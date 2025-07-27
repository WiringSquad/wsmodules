#include "ThreeStateCheckbox.hpp"

ThreeStateCheckbox::ThreeStateCheckbox(){
    state = ThreeState::DOESNT_MATTER;
    box.size = mm2px(Vec(4, 4));
}

void ThreeStateCheckbox::draw(const DrawArgs& args){
    NVGcontext* vg = args.vg;
    NVGcolor bg = nvgRGB(120, 120, 120);
    NVGcolor fal = nvgRGB(255, 0, 0);
    NVGcolor tr = nvgRGB(0, 255, 0);

    nvgBeginPath(vg);
    nvgFillColor(vg, bg);
    nvgRect(vg, 0, 0, mm2px(4), mm2px(4));
    nvgFill(vg);

    switch(state){
        case ThreeState::IF_FALSE:
            nvgBeginPath(vg);
            nvgFillColor(vg, fal);
            nvgRect(vg, mm2px(0.5), mm2px(0.5), mm2px(3), mm2px(3));
            nvgFill(vg);
            break;
        case ThreeState::IF_TRUE:
            nvgBeginPath(vg);
            nvgFillColor(vg, tr);
            nvgRect(vg, mm2px(0.5), mm2px(0.5), mm2px(3), mm2px(3));
            nvgFill(vg);
            break;
        default:
            break;
    }
}

void ThreeStateCheckbox::onDragEnd(const DragEndEvent& e){
    switch(static_cast<int>(floor(getParamQuantity()->getValue()))) {
        case 0:
            getParamQuantity()->setValue(1);
            state = ThreeState::IF_FALSE;
            break;
        case 1:
            getParamQuantity()->setValue(2);
            state = ThreeState::IF_TRUE;
            break;
        case 2:
            getParamQuantity()->setValue(0);
            state = ThreeState::DOESNT_MATTER;
            break;
        default:
            break;
    }
}