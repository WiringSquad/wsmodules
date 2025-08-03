#pragma once
#include "PolySample.hpp"
#include "PolySampleBuffer.hpp"

struct FoldUnit{
    static constexpr int delayBufSize = 4800;
    
    float thresh0;
    float thresh1;
    float thresh2;
    float thresh3;

    float gain0;
    float gain1;
    float gain2;
    float gain3;
    
    float shift0;
    float shift1;
    float shift2;
    float shift3;

    bool stagesActive[4];

    bool delayOn;

    PolySample psThresh;
    PolySample ngThresh;
    PolySample posFold;
    PolySample negFold;

    PolySample pipeline;
    float pipeline2;

    float posFoldFloat;
    float negFoldFloat;
    float psThreshFloat;
    float ngThreshFloat;

    float delay;

    PolySampleBuffer gteDelayMasks;
    PolySampleBuffer lteDelayMasks;

    PolySample gteMask;
    PolySample lteMask;
    
    float singleFold(float sam, float thresh, float gain, float shift);
    
    float multiFold(float sam);

    PolySample singleFold(PolySample sam, float thresh, float gain, float shift, int stageDelay);

    void updateFolds(float topThresh, float topGain, float topShift, float drop, bool* sA, bool delOn);

    PolySample multiFold(PolySample sam, float topThresh, float topGain, float topShift, float drop, bool* sA, float delay);

    FoldUnit();
};