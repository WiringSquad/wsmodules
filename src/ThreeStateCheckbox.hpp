#pragma once
#include "plugin.hpp"

enum class ThreeState{
    DOESNT_MATTER,
    IF_FALSE,
    IF_TRUE
};

struct ThreeStateCheckbox : ParamWidget{
    ThreeState state;

    ThreeStateCheckbox();

    void draw(const DrawArgs& args) override;

    void onDragEnd(const DragEndEvent& e) override;
};
