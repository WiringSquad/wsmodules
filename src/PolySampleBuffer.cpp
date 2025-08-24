#include "PolySample.hpp"
#include "PolySampleBuffer.hpp"
    
PolySampleBuffer::PolySampleBuffer(){}

PolySampleBuffer::PolySampleBuffer(int mS) : maxSize(mS){
    for(int i = 0; i < maxSize; i++){
        polyBuffer.push_back(PolySample());
    }
}

void PolySampleBuffer::pushNewSample(PolySample ps){
    if(polyBuffer.size() != 0 && polyBuffer.size() == maxSize){
        polyBuffer.pop_front();
    }
    polyBuffer.push_back(ps);
}

PolySample PolySampleBuffer::naiveBFD(float betwTime){
    return (polyBuffer[2] - polyBuffer[1]) / (betwTime);
}

PolySample PolySampleBuffer::naiveSecondOrderBFD(float betwTime){
    return (polyBuffer[2] - polyBuffer[1]*2 + polyBuffer[0]) / (betwTime * betwTime);
}

PolySample& PolySampleBuffer::operator[](size_t index){
    return polyBuffer[index];
}

const PolySample& PolySampleBuffer::operator[](size_t index) const {
    return polyBuffer[index];
}

/*PolySample& PolySampleBuffer::operator[](float index){
    PolySample mac = PolySample();
    for(int i = 0; i < maxSize; i++){
        mac += polyBuffer[i] * PolySample::sinc(M_PI * (index - i));
    }
    return mac;
}*/

//full quality resampling. not great
const PolySample PolySampleBuffer::resample(float index) const{
    PolySample mac = PolySample();
    for(int i = 0; i < maxSize; i++){
        mac += polyBuffer[i] * PolySample::sinc(M_PI * (index - i));
    }
    return mac;
}

const PolySampleBuffer& PolySampleBuffer::operator=(const PolySampleBuffer& other){
    if(this != &other){
        maxSize = other.maxSize;
        polyBuffer = other.polyBuffer;
    }
    return *this;
}



//stats tools

void sort(PolySampleBuffer& buf){
    PolySample lt;
    PolySample gte;
    
    for(int i = 0; i < buf.maxSize; i++){
        for(int j = 0; j < buf.maxSize - 1; j++){
            lt = PolySample::ifelse(buf.polyBuffer[j] < buf.polyBuffer[j + 1], buf.polyBuffer[j], buf.polyBuffer[j + 1]);
            gte = PolySample::ifelse(buf.polyBuffer[j] >= buf.polyBuffer[j + 1], buf.polyBuffer[j], buf.polyBuffer[j + 1]);
            buf[j] = lt;
            buf[j + 1] = gte;
        }
    }
}

PolySampleBuffer sort(const PolySampleBuffer& buf){
    PolySampleBuffer sortedBuf = buf;
    sort(sortedBuf);
    return sortedBuf;
}

PolySample min(const PolySampleBuffer& buf){
    return sort(buf)[0];
}

PolySample max(const PolySampleBuffer& buf){
    return sort(buf)[buf.maxSize];
}

PolySample mean(const PolySampleBuffer& buf){
    PolySample sum;
    for(int i = 0; i < buf.polyBuffer.size(); i++){
        sum += buf.polyBuffer[i];
    }
    return sum / buf.polyBuffer.size();
}

PolySample median(const PolySampleBuffer& buf){
    return PolySample(); //blank for now
}

PolySample variance(const PolySampleBuffer& buf){
    PolySample m = mean(buf);
    PolySample acc;

    for(int i = 0; i < buf.maxSize; i++){
        acc += PolySample::pow(buf[i] - m, 2);
    }

    return acc / buf.maxSize;
}

PolySample stddev(const PolySampleBuffer& buf){
    return PolySample::sqrt(variance(buf));
}

PolySample rms(const PolySampleBuffer& buf){
    PolySample acc;
    for(int i = 0; i < buf.maxSize; i++){
        acc += PolySample::pow(buf[i], 2);
    }
    return PolySample::sqrt(acc / buf.maxSize);
}

PolySample skew(const PolySampleBuffer& buf){
    PolySample acc;
    PolySample m = mean(buf);
    PolySample st = stddev(buf);
    for(int i = 0; i < buf.maxSize; i++){
        acc += PolySample::pow(buf[i] - m, 3);
    }
    return acc /((buf.maxSize - 1) * PolySample::pow(st, 3));
}