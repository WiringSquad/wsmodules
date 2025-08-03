#include "FoldUnit.hpp"

float FoldUnit::singleFold(float sam, float thresh, float gain, float shift){
    psThreshFloat = thresh;
    ngThreshFloat = thresh * -1;
    
    posFoldFloat = ((ngThreshFloat - sam) * gain) + ngThreshFloat + shift;
    negFoldFloat = psThreshFloat - ((sam - psThreshFloat)*gain) - shift;

    return (sam >= psThreshFloat ? posFoldFloat : (sam <= ngThreshFloat ? negFoldFloat : sam));
}

float FoldUnit::multiFold(float sam){
    pipeline2 = stagesActive[0] ? singleFold(sam, thresh0, gain0, shift0) : sam;
    pipeline2 = stagesActive[1] ? singleFold(pipeline2, thresh1, gain1, shift1) : pipeline2;
    pipeline2 = stagesActive[2] ? singleFold(pipeline2, thresh2, gain2, shift2) : pipeline2;
    return stagesActive[3] ? singleFold(pipeline2, thresh3, gain3, shift3) : pipeline2;
}

PolySample FoldUnit::singleFold(PolySample sam, float thresh, float gain, float shift, int stageDelay){
    psThresh = thresh;
    ngThresh = thresh * -1;

    posFold = ((ngThresh - sam)*gain) + ngThresh + shift; //formulas from design doc
    negFold = psThresh - ((sam - psThresh)*gain) - shift;
    
    gteMask = delayOn ? gteDelayMasks[stageDelay] : sam >= psThresh;
    lteMask = delayOn ? lteDelayMasks[stageDelay] : sam <= ngThresh;

    return PolySample::ifelse(gteMask, posFold, PolySample::ifelse(lteMask, negFold, sam));

}

void FoldUnit::updateFolds(float topThresh, float topGain, float topShift, float drop, bool* sA, bool delOn){
    thresh0 = topThresh;
    thresh1 = topThresh * 0.75 * drop;
    thresh2 = topThresh = 0.5 * drop;
    thresh3 = topThresh * 0.25 * drop;

    gain0 = topGain;
    gain1 = topGain * 0.75 * drop;
    gain2 = topGain * 0.5 * drop;
    gain3 = topGain * 0.25 * drop;

    shift0 = topShift;
    shift1 = topShift * 0.75 * drop;
    shift2 = topShift * 0.5 * drop;
    shift3 = topShift * 0.25 * drop;

    for(int i = 0; i < 4; i++){
        stagesActive[i] = *(sA + i);
    }

    delayOn = delOn;
}

PolySample FoldUnit::multiFold(PolySample sam, float topThresh, float topGain, float topShift, float drop, bool* sA, float del){
    updateFolds(topThresh, topGain, topShift, drop, sA, del > 0.f);
    gteDelayMasks.pushNewSample(sam >= topThresh);
    lteDelayMasks.pushNewSample(sam <= topThresh * -1);

    pipeline = stagesActive[0] ? singleFold(sam, thresh0, gain0, shift0, 0) : sam;
    pipeline = stagesActive[1] ? singleFold(pipeline, thresh1, gain1, shift1, clampSafe(static_cast<int>(round(del * delayBufSize)), 0, delayBufSize)) : pipeline; //intense bounds checking
    pipeline = stagesActive[2] ? singleFold(pipeline, thresh2, gain2, shift2, clampSafe(static_cast<int>(round(2 * del * delayBufSize)), 0, delayBufSize)) : pipeline;
    return stagesActive[3] ? singleFold(pipeline, thresh3, gain3, shift3, clampSafe(static_cast<int>(round(3 * del * delayBufSize)), 0, delayBufSize)) : pipeline;
}

FoldUnit::FoldUnit(){
    gteDelayMasks = PolySampleBuffer(delayBufSize);
    lteDelayMasks = PolySampleBuffer(delayBufSize);
}