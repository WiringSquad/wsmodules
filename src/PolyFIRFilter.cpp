#pragma once
#include "PolySample.hpp"
#include "PolySampleBuffer.hpp"
#include "PolyFilter.hpp"

enum class PolyFIRFilterState{
    HALF_IDEAL_LPF,
    HALF_IDEAL_HPF, 
    HALF_IDEAL_BFP,
    HALF_IDEAL_NOTCH,

};

struct PolyFIRFilter : PolyFilter{
    int size;
    PolySampleBuffer lastSams;
    PolySampleBuffer taps;
    
    PolyFIRFilter(){}

    PolyFIRFilter(int size){
        lastSams = PolySampleBuffer(size);
        taps = PolySampleBuffer(size);
    }

    //non-fft realtime implementation. I wrote this in 5 mins, it's not good
    PolySample process(PolySample currentX) override {
        PolySample pipeline;
        lastSams.pushNewSample(currentX);
        for(int i = 0; i < size; i++){
            pipeline = pipeline + (lastSams[i] * taps[i]);

        }
        return pipeline;
    }

};