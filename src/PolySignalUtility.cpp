#pragma once
#include "plugin.hpp"

struct PolySignalUtility : Module{
    enum ParamId {
        PARAMS_LEN
	};
	enum InputId {
        INPUTS_LEN
	};
	enum OutputId {
        OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

    PolySignalUtility(){
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        
    }
};

struct PolySignalUtilityWidget : ModuleWidget{
    PolySignalUtilityWidget(PolySignalUtility* module){
        setPanel(createPanel(asset::plugin(pluginInstance, "res/polysigplaceholder.svg")));
        if(module){setModule(module);}

    }
};

Model* modelPolySignalUtility = createModel<PolySignalUtility, PolySignalUtilityWidget>("polysignalutility");