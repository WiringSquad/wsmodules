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

enum class PolyFilterNonlinearityState{
    LINEAR,
    SC_ITN, //inverse tangent soft clip
    SC_SGM, //sigmoid soft clip
    IO_RM // internal oscillator ring modulation
};

struct PolyFilter{
    PolyFilterState state;
    PolyFilterNonlinearityState nlState;
    
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

    PolyFilter(PolyFilterState pfState, int sampleRate);

    PolyFilter(PolyFilterState pfState, PolySample co, PolySample reso, int sampleRate);

    virtual void setState(PolyFilterState filterState);

    virtual void setNonlinearityState(PolyFilterNonlinearityState distState);

    virtual void setAllStates(PolyFilterState filterState, PolyFilterNonlinearityState distState);
    
    virtual void setSampleRate(int sampleRate);
    
    virtual void updateCoefs(float A1, float A2, float B0, float B1, float B2);

    virtual void updateCoefs(PolySample A0, PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2);

    virtual void updateCoefsNormalized(PolySample A0, PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2);

    virtual void updateParams(float co, float reso);

    virtual void updateParams(PolySample co, PolySample reso);

    virtual void updateDownstreamParams();

    virtual void updateCoefs_AllTypes(PolySample co, PolySample reso);

    virtual PolySample process(PolySample currentX);

    virtual PolySample processNonlinearity(PolySample fbToProcess);
};

