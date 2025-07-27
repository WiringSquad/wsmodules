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
