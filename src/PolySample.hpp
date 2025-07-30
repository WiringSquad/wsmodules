#pragma once
#include "plugin.hpp"

struct PolySample {
    simd::float_4 chans0_3;
    simd::float_4 chans4_7;
    simd::float_4 chans8_11;
    simd::float_4 chans12_15;
    //float temp[16];

    // 16 samples for polyphonic input
    const float EPS = 0.0001f;

    //void setSample(Input inp); deprecated but still here

    PolySample();

    PolySample(float inp);

    std::string toString();
    
    void polySampleFromInput(Input& inp);

    void polySampleToOutput(Output& otp);
    
    PolySample& operator=(const float& value);
    
    PolySample& operator=(const PolySample& other);

    //optimization for the math: 
    //lots of adding of zeros. make an int to keep track of the number of channels active.
    //if a math op encounters a zero, it ignores it and increments a counter. 
    //if the counter hits the number of active channels, the operation ends automatically, and values are just copied over.
    //only update the number of active channels after an op that can turn zero values nonzero.
    
    PolySample operator+(const float& value) const;
    
    PolySample operator+(const PolySample& other) const;
    
    PolySample operator-(const float& value) const;
    
    PolySample operator-(const PolySample& other) const;
    
    PolySample operator*(const float& value) const;
    
    PolySample operator*(const PolySample& other) const;

    PolySample operator/(const float& value) const;

    PolySample operator/(const PolySample& other) const;

    //>= and <= here

    PolySample operator>=(const PolySample& other) const;

    PolySample operator<=(const PolySample& other) const;

    //TODO: add simd math funcs
    //add conversions to and from float[16] just in case

    static PolySample sin(PolySample arg);

    static PolySample cos(PolySample arg);

    static PolySample tan(PolySample arg);

    static PolySample atan(PolySample arg);

    static PolySample pow(PolySample arg, float p);

    static PolySample pow(PolySample arg, PolySample p);

    static PolySample exp(PolySample arg);
    
    //backwards finite difference
    static PolySample naive_bfd(PolySample lastSample, PolySample currentSample, float betwTime);

    //second order backwards finite difference
    static PolySample naive_second_order_bfd(PolySample twoSamplesAgo, PolySample lastSample, PolySample currentSample, float betwTime);

    static PolySample ifelse(PolySample mask, PolySample a, PolySample b);

    static PolySample crossfade(PolySample a, PolySample b, PolySample p);

    static PolySample crossfade(PolySample a, PolySample b, float p);

    
    
};