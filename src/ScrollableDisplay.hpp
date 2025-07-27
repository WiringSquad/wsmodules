#include "plugin.hpp"

enum class ScrollableDisplayType {
    NONE,
    QUANT,
    BOOL,
    COMP,
    OP
};

struct ScrollerData{
    enum QuantsData{
        BLANK_Q,
        M,
        dM,
        d2M,
        S,
        dS,
        d2S,
        A,
        dA,
        d2A,
        B,
        dB,
        d2B
    };

    enum BoolsData{
        BLANK_B,
        AND,
        OR,
        UNL,
        NND,
        NOR,
        XOR,
        XNR,
        IMP
    };

    enum CompsData{
        BLANK_C,
        EQ,
        NEQ,
        GT,
        LT,
        GTE,
        LTE
    };

    enum OpsData{
        BLANK_O,
        PLUS,
        MINUS,
        MUL,
        DIV,
        POWER,
        BALOGB, //base a log of b
        SIN,
        COS,
        TAN,
        ISIN,
        ICOS,
        ITAN
    };

    union DataUnion
    {
        QuantsData quants;
        BoolsData bools;
        CompsData comps;
        OpsData ops;
    };
    
    ScrollableDisplayType dataType;
    DataUnion data;

    // Constructors
    ScrollerData();

    ScrollerData(ScrollableDisplayType type);

    std::string getTag();

    int getSize();

    void setState(int inp);
};



struct ScrollableDisplay : ParamWidget {
    ScrollerData data;
    float SENSITIVITY = 0.001f;
    Svg spriteImg;
    bool controller;
    bool* listener;
    int svgIndex = 0;

    //ParamQuantity* paramQuantity = nullptr;
    
    int dispLength = 10; 
    //int numChars = 1;
    
    /*void onScroll(const ScrollEvent& e) override {
        e.consume(this);
    }*/
   //TODO: onDragMove is needed to update the slider sprite

    /*void onDragMove(const DragMoveEvent& e) override {
        if (e.button == GLFW_MOUSE_BUTTON_LEFT) {
            //data.scroll(e.mouseDelta.y < 0);
            e.consume(this);
        }
    }*/
    

    void draw(const DrawArgs& args) override;

    void onDragStart(const DragStartEvent& e) override;

    void onDragMove(const DragMoveEvent& e) override;

    void onDragEnd(const DragEndEvent& e) override;


    ScrollableDisplay();
   
    void setType(ScrollableDisplayType type);

    bool* getListener();

    bool* getController();
};