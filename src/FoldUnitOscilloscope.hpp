#pragma once
#include "plugin.hpp"
#include "FoldUnit.hpp"

struct FoldUnitOscilloscope : Widget {

    static constexpr int renderSteps = 256;

    float sinBuffer[renderSteps];

    FoldUnit* sFold;

    void setFoldPointer(FoldUnit* f);

    FoldUnitOscilloscope();

    void draw(const DrawArgs& args) override;

    


};