#pragma once 
#include "plugin.hpp"
#include "PolySample.hpp"
#include "PolySampleBuffer.hpp"

enum class PolyFilterState{
    LOWPASS_1P,
    HIGHPASS_1P,
    LOWPASS_2P,
    HIGHPASS_2P,
    HIGHPASS,
    BANDPASS,
    NOTCH,
    ALLPASS
};

struct PolyFilter{
    PolySample a0;
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
    PolySample alpha_1p;
    PolySample alpha_1p_hpf;

    PolySample Q;
    float fs;
    float res;


    PolyFilter();
    
    void updateCoefs(float A1, float A2, float B0, float B1, float B2);

    void updateCoefs(PolySample A0, PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2);

    void updateCoefsNormalized(PolySample A0, PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2);

    void updateParams(float co, float reso);

    void updateParams(PolySample co, PolySample reso);

    void updateDownstreamParams();

    void updateCoefs_AllTypes(PolyFilterState pfState);

    PolySample process(PolySample currentX);

};