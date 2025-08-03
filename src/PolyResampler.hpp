#pragma once
#include "PolySample.hpp"
#include "PolySampleBuffer.hpp"

struct PolyResampler{
    float sampleFreq;
    
    PolyResampler();

    PolyResampler(float freq);
    
    PolySample resample(PolySampleBuffer& buf, float pos);

    void setSampleRate(float freq);
};