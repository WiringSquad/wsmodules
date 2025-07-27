#pragma once
#include "plugin.hpp"
#include "FoldUnitOscilloscope.hpp"

FoldUnitOscilloscope::FoldUnitOscilloscope(){
    for(int i = 0; i < renderSteps; i++){
        sinBuffer[i] = sin((2 * M_PI / (renderSteps)) * i);
    }
}

void FoldUnitOscilloscope::setFoldPointer(FoldUnit* f){
    sFold = f;
}

void FoldUnitOscilloscope::draw(const DrawArgs& args){
    NVGcontext* vg = args.vg;
    NVGcolor bg = nvgRGB(120, 120, 120);
    NVGcolor line = nvgRGB(0,255, 0);

    nvgBeginPath(vg);
    nvgFillColor(vg, bg);
    nvgRect(vg, 0, 0, mm2px(Vec(20, 20)).x, mm2px(Vec(20, 20)).y); 
    nvgFill(vg);

    float toRender;

    nvgBeginPath(vg);
    nvgStrokeWidth(vg, 0.4f);
    nvgLineJoin(vg, NVG_ROUND);
    nvgLineCap(vg, NVG_ROUND);
    for(int i = 0; i < renderSteps; i++){
        toRender = sFold ? sFold->multiFold(sinBuffer[i] * 4) / 4 : sinBuffer[i];
        

        if(i == 0){
            nvgMoveTo(vg, mm2px(0), mm2px(10));
        }
        else{
            nvgLineTo(vg, mm2px(i) * (20.f / renderSteps), mm2px((10 - (8 * toRender))));
        }
    }
    nvgLineTo(vg, mm2px(20), mm2px(10));
    nvgStrokeColor(vg, line);
    nvgStroke(vg);
}