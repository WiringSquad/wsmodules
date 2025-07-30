#include "plugin.hpp"

struct SwapButton : ParamWidget {
    ParamQuantity* Bool1 = nullptr;
    ParamQuantity* LHS1 = nullptr;
    ParamQuantity* Comp1 = nullptr;
    ParamQuantity* RHS1 = nullptr;
    ParamQuantity* Bool2 = nullptr;
    ParamQuantity* LHS2 = nullptr;
    ParamQuantity* Comp2 = nullptr;
    ParamQuantity* RHS2 = nullptr;
    
    void setPtrs(ParamQuantity* bool1, ParamQuantity* lhs1, ParamQuantity* comp1, ParamQuantity* rhs1,
                    ParamQuantity* bool2, ParamQuantity* lhs2, ParamQuantity* comp2, ParamQuantity* rhs2);
    
    void swap();

    SwapButton();

    void onDragStart(const DragStartEvent& e) override;

    void onDragEnd(const DragEndEvent& e) override;

    void onDragDrop(const DragDropEvent& e) override;

    void draw(const DrawArgs& args) override;

};