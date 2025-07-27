#include "ScrollableDisplay.hpp"


    

// Constructors
ScrollerData::ScrollerData() : dataType(ScrollableDisplayType::NONE), data() {}

ScrollerData::ScrollerData(ScrollableDisplayType type){
    dataType = type;
    switch (type) {
        case ScrollableDisplayType::QUANT:
            data.quants = QuantsData::BLANK_Q;
            break;
        case ScrollableDisplayType::BOOL:
            data.bools = BoolsData::BLANK_B;
            break;
        case ScrollableDisplayType::COMP:
            data.comps = CompsData::BLANK_C;
            break;
        case ScrollableDisplayType::OP:
            data.ops = OpsData::BLANK_O;
            break;
        default:
            dataType = ScrollableDisplayType::NONE;
            break;
    }
}

std::string ScrollerData::getTag(){
    switch (dataType) {
        case ScrollableDisplayType::QUANT:
            switch (data.quants) {
                case QuantsData::BLANK_Q: return "Blank";
                case QuantsData::M: return "M";
                case QuantsData::dM: return "dM";
                case QuantsData::d2M: return "d2M";
                case QuantsData::S: return "S";
                case QuantsData::dS: return "dS";
                case QuantsData::d2S: return "d2S";
                case QuantsData::A: return "A";
                case QuantsData::dA: return "dA";
                case QuantsData::d2A: return "d2A";
                case QuantsData::B: return "B";
                case QuantsData::dB: return "dB";
                case QuantsData::d2B: return "d2B";
                default: return "none";
            }
        case ScrollableDisplayType::BOOL:
            switch (data.bools) {
                case BoolsData::BLANK_B: return "Blank";
                case BoolsData::AND: return "AND";
                case BoolsData::OR: return "OR";
                case BoolsData::UNL: return "UNL"; //unless
                case BoolsData::NND: return "NND"; //nand
                case BoolsData::NOR: return "NOR"; //nor
                case BoolsData::XOR: return "XOR"; //xor
                case BoolsData::XNR: return "XNR"; //xnor
                case BoolsData::IMP: return "IMP"; //implication
                default: return "none";
            }
        case ScrollableDisplayType::COMP:
            switch (data.comps) {
                case CompsData::BLANK_C: return "Blank";
                case CompsData::EQ: return "=";
                case CompsData::NEQ: return "!=";
                case CompsData::GT: return ">"; 
                case CompsData::LT: return "<"; 
                case CompsData::GTE: return ">="; 
                case CompsData::LTE: return "<="; 
                default: return "none";
            }
        case ScrollableDisplayType::OP:
            switch (data.ops) {
                case OpsData::BLANK_O: return "Blank";
                case OpsData::PLUS: return "+";
                case OpsData::MINUS: return "-";
                case OpsData::MUL: return "*";
                case OpsData::DIV: return "/";
                case OpsData::POWER: return "^";
                case OpsData::BALOGB: return "log_b(a)"; //base a log of b
                case OpsData::SIN: return "sin";
                case OpsData::COS: return "cos";
                case OpsData::TAN: return "tan";
                case OpsData::ISIN: return "isn";
                case OpsData::ICOS: return "ics";
                case OpsData::ITAN: return "itn";
                default: return "none";
            }
        default:
            break;
    }
}

int ScrollerData::getSize() {
    switch (dataType) {
        case ScrollableDisplayType::QUANT:
            return 13; // 0-12
        case ScrollableDisplayType::BOOL:
            return 10; // 0-9
        case ScrollableDisplayType::COMP:
            return 7; // 0-6
        case ScrollableDisplayType::OP:
            return 7; // 0-6
        default:
            return 0;
    }
}

void ScrollerData::setState(int inp){
    switch(dataType){
        case ScrollableDisplayType::QUANT:
            data.quants = static_cast<QuantsData>(inp);
            break;
        case ScrollableDisplayType::BOOL:
            data.bools = static_cast<BoolsData>(inp);
            break;
        case ScrollableDisplayType::COMP:
            data.comps = static_cast<CompsData>(inp);
            break;
        case ScrollableDisplayType::OP:
            data.ops = static_cast<OpsData>(inp);
            break;
        default:
            break;
    }       

}







    //ParamQuantity* paramQuantity = nullptr;
    
    
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
    

void ScrollableDisplay::draw(const DrawArgs& args) {
    BNDwidgetState state = BND_DEFAULT;
    //DEBUG("Getting index");

    svgIndex = floor(getParamQuantity()->getValue());
    switch(data.dataType){
        case ScrollableDisplayType::OP:
            controller = (svgIndex >= 7); //change later
    }
    
    //DEBUG("Setting state");
    data.setState(listener && *listener ? 0 : svgIndex);

    if (APP->event->hoveredWidget == this)
        state = BND_HOVER;
    if (APP->event->draggedWidget == this)
        state = BND_ACTIVE;

    float progress = getParamQuantity() ? getParamQuantity()->getScaledValue() : 0.f;
    std::string text = getParamQuantity() ? getParamQuantity()->getString() : "";
    
    //DEBUG("Getting context");
    NVGcontext *vg = args.vg;
    NVGcolor bg = nvgRGB(0, 255, 255);
    //draw background
    nvgBeginPath(vg);
    nvgFillColor(vg, bg);
    nvgRect(vg, 0, 0, mm2px(Vec(10, 10)).x, mm2px(Vec(10, 10)).y); 
    nvgFill(vg);

    //DEBUG("Getting sprite");
    //draw sprite
    nvgBeginPath(vg);
    switch(data.dataType){
        case ScrollableDisplayType::QUANT:
            quantSvgCache[listener && *listener ? 0 : svgIndex]->draw(vg);
            break;
        case ScrollableDisplayType::COMP:
            compSvgCache[svgIndex]->draw(vg);
            break;
        case ScrollableDisplayType::OP:
            opSvgCache[svgIndex]->draw(vg);
            break;
        case ScrollableDisplayType::BOOL:
            boolSvgCache[svgIndex]->draw(vg);
            break;
        default:
            break;
    }
}

void ScrollableDisplay::onDragStart(const DragStartEvent& e){
    e.consume(this);
    if (e.button != GLFW_MOUSE_BUTTON_LEFT){
        return;
    }
    
    //DEBUG("Drag started");
    APP->window->cursorLock();
}

void ScrollableDisplay::onDragMove(const DragMoveEvent& e){
    if (getParamQuantity() && ! (listener && *listener)) {
        if(getParamQuantity()->getValue() == 0.f && e.mouseDelta.y > 0){
            getParamQuantity()->setValue(getParamQuantity()->getMaxValue() - 0.001f);
        }
        else if(getParamQuantity()->getValue() >= getParamQuantity()->getMaxValue() - 0.02f && e.mouseDelta.y < 0){
            getParamQuantity()->setValue(getParamQuantity()->getMinValue());
        }
        else{
            getParamQuantity()->moveScaledValue(SENSITIVITY * -e.mouseDelta.y);
        }


        //getParamQuantity()->moveScaledValue(SENSITIVITY * -e.mouseDelta.y);
        //getParamQuantity()->setValue(getParamQuantity()->getValue())
    }
}

void ScrollableDisplay::onDragEnd(const DragEndEvent& e){
    //DEBUG("Drag ended");
    getParamQuantity()->setValue(floor(getParamQuantity()->getValue()) + 0.5f);
    DEBUG(data.getTag().c_str());
    APP->window->cursorUnlock();
}



ScrollableDisplay::ScrollableDisplay() : ParamWidget() {
    data = ScrollerData();
    
    box.size = mm2px(Vec(10, 10)); 
}

void ScrollableDisplay::setType(ScrollableDisplayType type) {
    data = ScrollerData(type);
    
    switch(type){
        case ScrollableDisplayType::QUANT:
            //spriteImg = APP->window->loadSvg(asset::plugin(pluginInstance, "res/quantspritesheet.svg"));
            //spriteImg.loadFile(asset::plugin(pluginInstance, "res/quantspritesheet.svg"));
            break;
        default:
            break;
    }
}

bool* ScrollableDisplay::getListener() {
    return listener;
}

bool* ScrollableDisplay::getController() {
    return &controller;
}
