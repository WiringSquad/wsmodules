#include "plugin.hpp"
#include "SwapButton.hpp"
    
void SwapButton::setPtrs(ParamQuantity* bool1, ParamQuantity* lhs1, ParamQuantity* comp1, ParamQuantity* rhs1,
                ParamQuantity* bool2, ParamQuantity* lhs2, ParamQuantity* comp2, ParamQuantity* rhs2) {
    Bool1 = bool1;
    LHS1 = lhs1;
    Comp1 = comp1;
    RHS1 = rhs1;
    Bool2 = bool2;
    LHS2 = lhs2;
    Comp2 = comp2;
    RHS2 = rhs2;
}

void SwapButton::swap(){
    if(Bool1 && Bool2){
        float temp = Bool1->getValue();
        Bool1->setValue(Bool2->getValue());
        Bool2->setValue(temp);
    }
    if(LHS1 && LHS2 && Comp1 && Comp2 && RHS1 && RHS2){
        float temp = LHS1->getValue();
        LHS1->setValue(LHS2->getValue());
        LHS2->setValue(temp);

        temp = Comp1->getValue();
        Comp1->setValue(Comp2->getValue());
        Comp2->setValue(temp);

        temp = RHS1->getValue();
        RHS1->setValue(RHS2->getValue());
        RHS2->setValue(temp);
    }
}

SwapButton::SwapButton() {
    box.size = mm2px(Vec(10, 10));
}

void SwapButton::onDragStart(const DragStartEvent& e) {
    e.consume(this);
    getParamQuantity()->setValue(1.f); // Set the parameter to 1 when dragging starts
}

void SwapButton::onDragEnd(const DragEndEvent& e) {
    e.consume(this);
    getParamQuantity()->setValue(0.f); // Reset the parameter to 0 when dragging ends
}

void SwapButton::onDragDrop(const DragDropEvent& e) {
    e.consume(this);
    swap();
}

void SwapButton::draw(const DrawArgs& args) {
    BNDwidgetState state = BND_DEFAULT;
    if (APP->event->hoveredWidget == this)
        state = BND_HOVER;
    if (APP->event->draggedWidget == this) 
        state = BND_ACTIVE;

    NVGcontext *vg = args.vg;
    nvgBeginPath(vg);
    nvgFillColor(vg, nvgRGB(0, 255, 0));
    nvgRect(vg, 0, 0, mm2px(Vec(10, 10)).x, mm2px(Vec(10, 10)).y); 
    nvgFill(vg);
}

