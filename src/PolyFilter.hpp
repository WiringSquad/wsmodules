#pragma once 
#include "plugin.hpp"
#include "PolySample.hpp"
#include "PolySampleBuffer.hpp"

enum class PolyFilterState{
    UNITY,
    LOWPASS_1P,
    HIGHPASS_1P,
    LOWPASS_2P,
    HIGHPASS_2P,
    HIGHPASS,
    BANDPASS,
    NOTCH,
    ALLPASS,
    PEAKING,
    LOWSHELF,
    HIGHSHELF
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
    PolySample big_A;

    PolySample Q;
    float fs;
    float res;
    float gain;


    PolyFilter();
    
    virtual void updateCoefs(float A1, float A2, float B0, float B1, float B2);

    virtual void updateCoefs(PolySample A0, PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2);

    virtual void updateCoefsNormalized(PolySample A0, PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2);

    virtual void updateParams(float co, float reso);

    virtual void updateParams(PolySample co, PolySample reso);

    virtual void updateDownstreamParams();

    virtual void updateCoefs_AllTypes(PolyFilterState pfState);

    virtual PolySample process(PolySample currentX);

};