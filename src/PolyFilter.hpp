#pragma once 
#include "plugin.hpp"
#include "PolySample.hpp"
#include "PolySampleBuffer.hpp"

enum class PolyFilterState{
    LOWPASS,
    HIGHPASS,
    BANDPASS,
    NOTCH,
    ALLPASS
};

struct PolyFilter{
    PolySample a1;
    PolySample a2;
    PolySample b0;
    PolySample b1;
    PolySample b2;

    PolySampleBuffer xt;
    PolySampleBuffer yt;

    PolySample f0;
    PolySample omega0;
    PolySample cos_omega0;
    PolySample sin_omega0;
    PolySample alpha;

    PolySample Q;
    float fs;
    float res;


    PolyFilter();
    
    void updateCoefs(float A1, float A2, float B0, float B1, float B2);

    void updateCoefs(PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2);

    void updateCoefsNormalized(PolySample A0, PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2);

    void updateParams(float co, float reso);

    void updateParams(PolySample co, PolySample reso);

    void updateDownstreamParams();

    void updateCoefs_AllTypes(PolyFilterState pfState);

    PolySample process(PolySample currentX);

};