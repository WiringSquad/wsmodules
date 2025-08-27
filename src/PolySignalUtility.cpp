#include "plugin.hpp"
#include "PolyUtils.hpp"

struct PolySignalUtility : Module{
    enum ParamId {
        MORPH_PARAM,
        LITER_ONE_TYPE_PARAM,
        LITER_TWO_TYPE_PARAM,
        LITER_THREE_TYPE_PARAM,
        LITER_FOUR_TYPE_PARAM,
        LITER_FIVE_TYPE_PARAM,
        LITER_SIX_TYPE_PARAM,

        OP_ONE_TYPE_PARAM,
        OP_TWO_TYPE_PARAM,
        PARAMS_LEN
	};
	enum InputId {
        LITER_ONE_INPUT,
        LITER_TWO_INPUT,
        LITER_THREE_INPUT,
        LITER_FOUR_INPUT,
        LITER_FIVE_INPUT,
        LITER_SIX_INPUT,

        OP_ONE_LHS_INPUT,
        OP_ONE_RHS_INPUT,
        OP_ONE_INTERLEAVE_INPUT,
        
        OP_TWO_LHS_INPUT,
        OP_TWO_RHS_INPUT,
        OP_TWO_INTERLEAVE_INPUT,
        INPUTS_LEN
	};
	enum OutputId {
        MORPH_OUTPUT,

        LITER_ONE_OUTPUT,
        LITER_TWO_OUTPUT,
        LITER_THREE_OUTPUT,
        LITER_FOUR_OUTPUT,
        LITER_FIVE_OUTPUT,
        LITER_SIX_OUTPUT,

        OP_ONE_OUTPUT,
        OP_TWO_OUTPUT,
        OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

    PolySignalUtility(){
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        int len = static_cast<int>(PolyLiterals::LITERS_LEN);
        int opslen = static_cast<int>(PolyOperations::OPERS_LEN);
        configParam(MORPH_PARAM, -10, 10, 0, "Morph");
        configParam(LITER_ONE_TYPE_PARAM, 0, len, 0, "Literal One Type");
        configParam(LITER_TWO_TYPE_PARAM, 0, len, 0, "Literal Two Type");
        configParam(LITER_THREE_TYPE_PARAM, 0, len, 0, "Literal Three Type");
        configParam(LITER_FOUR_TYPE_PARAM, 0, len, 0, "Literal Four Type");
        configParam(LITER_FIVE_TYPE_PARAM, 0, len, 0, "Literal Five Type");
        configParam(LITER_SIX_TYPE_PARAM, 0, len, 0, "Literal Six Type");
        
        configParam(OP_ONE_TYPE_PARAM, 0, opslen, 0, "Op One Type");
        configParam(OP_TWO_TYPE_PARAM, 0, opslen, 0, "Op One Type");

        configInput(LITER_ONE_INPUT, "Literal One");
        configInput(LITER_TWO_INPUT, "Literal Two");
        configInput(LITER_THREE_INPUT, "Literal Three");
        configInput(LITER_FOUR_INPUT, "Literal Four");
        configInput(LITER_FIVE_INPUT, "Literal Five");
        configInput(LITER_SIX_INPUT, "Literal Six");

        configInput(OP_ONE_LHS_INPUT, "Operator One LHS");
        configInput(OP_ONE_RHS_INPUT, "Operator One RHS");
        configInput(OP_ONE_INTERLEAVE_INPUT, "Operator One Interleave");

        configInput(OP_TWO_LHS_INPUT, "Operator Two LHS");
        configInput(OP_TWO_RHS_INPUT, "Operator Two RHS");
        configInput(OP_TWO_INTERLEAVE_INPUT, "Operator Two Interleave");

        configOutput(MORPH_OUTPUT, "Morph");
        
        configOutput(LITER_ONE_OUTPUT, "Literal One");
        configOutput(LITER_TWO_OUTPUT, "Literal Two");
        configOutput(LITER_THREE_OUTPUT, "Literal Three");
        configOutput(LITER_FOUR_OUTPUT, "Literal Four");
        configOutput(LITER_FIVE_OUTPUT, "Literal Five");
        configOutput(LITER_SIX_OUTPUT, "Literal Six");

        configOutput(OP_ONE_OUTPUT, "Operator One");
        configOutput(OP_TWO_OUTPUT, "Operator Two");
    }

    PolySample morph;

    PolySample processedLiterOne;
    PolySample processedLiterTwo;
    PolySample processedLiterThree;
    PolySample processedLiterFour;
    PolySample processedLiterFive;
    PolySample processedLiterSix;

    PolySample lhsOne;
    PolySample rhsOne;
    PolySample itlOne;
    
    PolySample lhsTwo;
    PolySample rhsTwo;
    PolySample itlTwo;

    PolySample postOpOne;
    PolySample postOpTwo;

    void process(const ProcessArgs& args) override{
        morph = params[MORPH_PARAM].getValue();
        PolySample::polySampleToOutput(morph, outputs[MORPH_OUTPUT]);

        PolySample::polySampleFromInput(processedLiterOne, inputs[LITER_ONE_INPUT]);
        PolySample::polySampleFromInput(processedLiterTwo, inputs[LITER_TWO_INPUT]);
        PolySample::polySampleFromInput(processedLiterThree, inputs[LITER_THREE_INPUT]);
        PolySample::polySampleFromInput(processedLiterFour, inputs[LITER_FOUR_INPUT]);
        PolySample::polySampleFromInput(processedLiterFive, inputs[LITER_FIVE_INPUT]);
        PolySample::polySampleFromInput(processedLiterSix, inputs[LITER_SIX_INPUT]);

        PolySample::polySampleFromInput(lhsOne, inputs[OP_ONE_LHS_INPUT]);
        PolySample::polySampleFromInput(rhsOne, inputs[OP_ONE_RHS_INPUT]);
        PolySample::polySampleFromInput(itlOne, inputs[OP_ONE_INTERLEAVE_INPUT]);
        PolySample::polySampleFromInput(lhsTwo, inputs[OP_TWO_LHS_INPUT]);
        PolySample::polySampleFromInput(rhsTwo, inputs[OP_TWO_RHS_INPUT]);
        PolySample::polySampleFromInput(itlTwo, inputs[OP_TWO_INTERLEAVE_INPUT]);

        processedLiterOne *= getPolyLiteral(static_cast<PolyLiterals>(params[LITER_ONE_TYPE_PARAM].getValue()));
        processedLiterTwo *= getPolyLiteral(static_cast<PolyLiterals>(params[LITER_TWO_TYPE_PARAM].getValue()));
        processedLiterThree *= getPolyLiteral(static_cast<PolyLiterals>(params[LITER_THREE_TYPE_PARAM].getValue()));
        processedLiterFour *= getPolyLiteral(static_cast<PolyLiterals>(params[LITER_FOUR_TYPE_PARAM].getValue()));
        processedLiterFive *= getPolyLiteral(static_cast<PolyLiterals>(params[LITER_FIVE_TYPE_PARAM].getValue()));
        processedLiterSix *= getPolyLiteral(static_cast<PolyLiterals>(params[LITER_SIX_TYPE_PARAM].getValue()));

        postOpOne = getPolyOperation(lhsOne, rhsOne, itlOne, static_cast<PolyOperations>(params[OP_ONE_TYPE_PARAM].getValue()));
        postOpTwo = getPolyOperation(lhsTwo, rhsTwo, itlTwo, static_cast<PolyOperations>(params[OP_TWO_TYPE_PARAM].getValue()));
        
        PolySample::polySampleToOutput(processedLiterOne, outputs[LITER_ONE_OUTPUT]);
        PolySample::polySampleToOutput(processedLiterTwo, outputs[LITER_TWO_OUTPUT]);
        PolySample::polySampleToOutput(processedLiterThree, outputs[LITER_THREE_OUTPUT]);
        PolySample::polySampleToOutput(processedLiterFour, outputs[LITER_FOUR_OUTPUT]);
        PolySample::polySampleToOutput(processedLiterFive, outputs[LITER_FIVE_OUTPUT]);
        PolySample::polySampleToOutput(processedLiterSix, outputs[LITER_SIX_OUTPUT]);

        PolySample::polySampleToOutput(postOpOne, outputs[OP_ONE_OUTPUT]);
        PolySample::polySampleToOutput(postOpTwo, outputs[OP_TWO_OUTPUT]);



    }

};

struct PolySignalUtilityWidget : ModuleWidget{
    PolySignalUtilityWidget(PolySignalUtility* module){
        setPanel(createPanel(asset::plugin(pluginInstance, "res/polysigplaceholder.svg")));
        if(module){setModule(module);}

        addParam(createParam<RoundBlackKnob>(mm2px(Vec(5.0, 5.0)), module, PolySignalUtility::MORPH_PARAM));
        addParam(createParam<RoundBlackKnob>(mm2px(Vec(15.0, 20.0)), module, PolySignalUtility::LITER_ONE_TYPE_PARAM));
        addParam(createParam<RoundBlackKnob>(mm2px(Vec(15.0, 30.0)), module, PolySignalUtility::LITER_TWO_TYPE_PARAM));
        addParam(createParam<RoundBlackKnob>(mm2px(Vec(15.0, 40.0)), module, PolySignalUtility::LITER_THREE_TYPE_PARAM));
        addParam(createParam<RoundBlackKnob>(mm2px(Vec(15.0, 50.0)), module, PolySignalUtility::LITER_FOUR_TYPE_PARAM));
        addParam(createParam<RoundBlackKnob>(mm2px(Vec(15.0, 60.0)), module, PolySignalUtility::LITER_FIVE_TYPE_PARAM));
        addParam(createParam<RoundBlackKnob>(mm2px(Vec(15.0, 70.0)), module, PolySignalUtility::LITER_SIX_TYPE_PARAM));

        addParam(createParam<RoundBlackKnob>(mm2px(Vec(35.0, 80.0)), module, PolySignalUtility::OP_ONE_TYPE_PARAM));
        addParam(createParam<RoundBlackKnob>(mm2px(Vec(35.0, 90.0)), module, PolySignalUtility::OP_TWO_TYPE_PARAM));

        addInput(createInput<PJ301MPort>(mm2px(Vec(5.0, 20.0)), module, PolySignalUtility::LITER_ONE_INPUT));
        addInput(createInput<PJ301MPort>(mm2px(Vec(5.0, 30.0)), module, PolySignalUtility::LITER_TWO_INPUT));
        addInput(createInput<PJ301MPort>(mm2px(Vec(5.0, 40.0)), module, PolySignalUtility::LITER_THREE_INPUT));
        addInput(createInput<PJ301MPort>(mm2px(Vec(5.0, 50.0)), module, PolySignalUtility::LITER_FOUR_INPUT));
        addInput(createInput<PJ301MPort>(mm2px(Vec(5.0, 60.0)), module, PolySignalUtility::LITER_FIVE_INPUT));
        addInput(createInput<PJ301MPort>(mm2px(Vec(5.0, 70.0)), module, PolySignalUtility::LITER_SIX_INPUT));

        addInput(createInput<PJ301MPort>(mm2px(Vec(5.0, 80.0)), module, PolySignalUtility::OP_ONE_LHS_INPUT));
        addInput(createInput<PJ301MPort>(mm2px(Vec(15.0, 80.0)), module, PolySignalUtility::OP_ONE_RHS_INPUT));
        addInput(createInput<PJ301MPort>(mm2px(Vec(25.0, 80.0)), module, PolySignalUtility::OP_ONE_INTERLEAVE_INPUT));
        addInput(createInput<PJ301MPort>(mm2px(Vec(5.0, 90.0)), module, PolySignalUtility::OP_TWO_LHS_INPUT));
        addInput(createInput<PJ301MPort>(mm2px(Vec(15.0, 90.0)), module, PolySignalUtility::OP_TWO_RHS_INPUT));
        addInput(createInput<PJ301MPort>(mm2px(Vec(25.0, 90.0)), module, PolySignalUtility::OP_TWO_INTERLEAVE_INPUT));
        
        addOutput(createOutput<PJ301MPort>(mm2px(Vec(15.0, 5.0)), module, PolySignalUtility::MORPH_OUTPUT));
        
        addOutput(createOutput<PJ301MPort>(mm2px(Vec(35.0, 20.0)), module, PolySignalUtility::LITER_ONE_OUTPUT));
        addOutput(createOutput<PJ301MPort>(mm2px(Vec(35.0, 30.0)), module, PolySignalUtility::LITER_TWO_OUTPUT));
        addOutput(createOutput<PJ301MPort>(mm2px(Vec(35.0, 40.0)), module, PolySignalUtility::LITER_THREE_OUTPUT));
        addOutput(createOutput<PJ301MPort>(mm2px(Vec(35.0, 50.0)), module, PolySignalUtility::LITER_FOUR_OUTPUT));
        addOutput(createOutput<PJ301MPort>(mm2px(Vec(35.0, 60.0)), module, PolySignalUtility::LITER_FIVE_OUTPUT));
        addOutput(createOutput<PJ301MPort>(mm2px(Vec(35.0, 70.0)), module, PolySignalUtility::LITER_SIX_OUTPUT));

        addOutput(createOutput<PJ301MPort>(mm2px(Vec(55.0, 80.0)), module, PolySignalUtility::OP_ONE_OUTPUT));
        addOutput(createOutput<PJ301MPort>(mm2px(Vec(55.0, 90.0)), module, PolySignalUtility::OP_TWO_OUTPUT));
    }
};

Model* modelPolySignalUtility = createModel<PolySignalUtility, PolySignalUtilityWidget>("polysignalutility");