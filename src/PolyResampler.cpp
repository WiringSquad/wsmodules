#include "PolyResampler.hpp"

PolyResampler::PolyResampler(){}

PolyResampler::PolyResampler(float freq) : sampleFreq(freq){}

float sampleFreq;
PolySample PolyResampler::resample(PolySampleBuffer& buf, float pos){
    PolySample resam = PolySample();
    for(int i = 0; i < buf.polyBuffer.size(); i++){ //maybe add size method to buffer later 
        resam = resam + buf[i] * PolySample::sinc(M_PI /* sampleFreq */* (pos - i));
    }   
}

void PolyResampler::setSampleRate(float freq){
    sampleFreq = freq;
}
