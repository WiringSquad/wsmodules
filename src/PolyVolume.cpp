#include "PolySample.hpp"
#include "PolySampleBuffer.hpp"
#include "PolyFilter.hpp" 

struct PolyVolume{
    PolySampleBuffer buf;
    PolyFilter smoother;

    PolySample peak;
    PolySample envelope;
    PolySample Rms;
    PolySample avg;

    int maxSize = 0;

    PolyVolume(){
        smoother = PolyFilter(PolyFilterState::LOWPASS_1P, 48000);
    }

    PolyVolume(int mS){
        maxSize = mS;
        buf = PolySampleBuffer(mS);
        smoother = PolyFilter(PolyFilterState::LOWPASS_1P, 48000);
    }

    void process(PolySample inp){
        buf.pushNewSample(inp);
        envelope = smoother.process(PolySample::abs(inp));
        avg = mean(buf);
        Rms = rms(buf);
        peak = max(buf);
    } 
};