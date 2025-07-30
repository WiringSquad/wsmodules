
#include "plugin.hpp"
#include "PolySample.hpp"
#include "ScrollableDisplay.hpp"
#include "FoldUnit.hpp"
#include "FoldUnitOscilloscope.hpp"
#include "ThreeStateCheckbox.hpp"
#include "PolyFilter.hpp"
#include "SwapButton.hpp"



struct Octoplus : Module {
	enum ParamId {
		//input params
        MAIN_PREBIAS_DC_AMP_PARAM,
        MAIN_PREBIAS_EXT_GAIN_PARAM,
        SIDE_PREBIAS_DC_AMP_PARAM,
        SIDE_PREBIAS_EXT_GAIN_PARAM,

        //prefold params
        PREFOLD_GAIN_PARAM,
        PREFOLD_OFFSET_PARAM,
        PREFOLD_DISPERSE_PARAM,
        PREFOLD_THRESH_DROP_PARAM,
        PREFOLD_CROSS_LENGTH_PARAM,

        PREFOLD_FILTER_CUTOFF_PARAM,
        PREFOLD_FILTER_RESONANCE_PARAM,

        //rect knob params
        RECT_GAIN_PARAM,
        RECT_PASSES_PARAM, 
        RECT_BLEND_PARAM,
        RECT_STEREO_CROSS_PARAM,

        //rect mod params
        RECT_QUANT_TO_MOD_PARAM,
        RECT_QUANT_ATTR_TO_MOD_PARAM,
        RECT_QUANT_LISTEN_TO_PARAM,

        //rect var params
        VAR_A_SET_LHS_PARAM,
        VAR_A_SET_OP_PARAM,
        VAR_A_SET_RHS_PARAM,

        VAR_B_SET_LHS_PARAM,
        VAR_B_SET_OP_PARAM,
        VAR_B_SET_RHS_PARAM,

        //rect condition params
        COND_1_SET_LHS_PARAM,
        COND_1_SET_COMP_PARAM,
        COND_1_SET_RHS_PARAM,

        COND_2_SET_BOOL_PARAM,
        COND_2_SET_LHS_PARAM,
        COND_2_SET_COMP_PARAM,
        COND_2_SET_RHS_PARAM,

        COND_3_SET_BOOL_PARAM,
        COND_3_SET_LHS_PARAM,
        COND_3_SET_COMP_PARAM,
        COND_3_SET_RHS_PARAM,

        COND_4_SET_BOOL_PARAM,
        COND_4_SET_LHS_PARAM,
        COND_4_SET_COMP_PARAM,
        COND_4_SET_RHS_PARAM,

        //swap params
        SWAP_QUANT_A_B_PARAM,
        SWAP_COND_1_2_PARAM,
        SWAP_COND_2_3_PARAM,
        SWAP_COND_3_4_PARAM,

        //postfold params
        POSTFOLD_GAIN_PARAM,
        POSTFOLD_OFFSET_PARAM,
        POSTFOLD_DISPERSE_PARAM,
        POSTFOLD_THRESH_DROP_PARAM,
        POSTFOLD_CROSS_LENGTH_PARAM,

        POSTFOLD_FILTER_CUTOFF_PARAM,
        POSTFOLD_FILTER_RESONANCE_PARAM,

        //output params
        MASTER_OUT_GAIN_PARAM,
        MASTER_OUT_PAN_PARAM,
        
        CUSTOM_OUT_ONE_GAIN_PARAM,
        CUSTOM_OUT_ONE_PAN_PARAM,
        CUSTOM_OUT_ONE_THREE_STATE_M,
        CUSTOM_OUT_ONE_THREE_STATE_DM,
        CUSTOM_OUT_ONE_THREE_STATE_D2M,

        CUSTOM_OUT_TWO_GAIN_PARAM,
        CUSTOM_OUT_TWO_PAN_PARAM,
        CUSTOM_OUT_TWO_THREE_STATE_M,
        CUSTOM_OUT_TWO_THREE_STATE_DM,
        CUSTOM_OUT_TWO_THREE_STATE_D2M,

        
        FREE_OUT_GAIN_PARAM,
        FREE_OUT_PAN_PARAM,
        FREE_OUT_THREE_STATE_M,
        FREE_OUT_THREE_STATE_DM,
        FREE_OUT_THREE_STATE_D2M,

        PARAMS_LEN
	};
	enum InputId {
		//audio sigins
        MAIN_LEFT_OR_MONO_INPUT,
        MAIN_RIGHT_INPUT,
        MAIN_PREBIAS_LEFT_OR_MONO_INPUT,
        MAIN_PREBIAS_RIGHT_INPUT,
        SIDE_LEFT_OR_MONO_INPUT,
        SIDE_RIGHT_INPUT,
        SIDE_PREBIAS_LEFT_OR_MONO_INPUT,
        SIDE_PREBIAS_RIGHT_INPUT,

        //prefold mod sigins
        PREFOLD_PLEAT_GAIN_INPUT,
        PREFOLD_PLEAT_OFFSET_INPUT,
        PREFOLD_PLEAT_DISPERSE_INPUT,
        PREFOLD_PLEAT_THRESH_DROP_INPUT,

        //rect mod sigins

        RECT_QUANT_GAIN_INPUT,
        RECT_NUM_PASSES_INPUT,
        RECT_CONDITION_BLEND_INPUT,

        //postfold mod sigins
        POSTFOLD_PLEAT_GAIN_INPUT,
        POSTFOLD_PLEAT_OFFSET_INPUT,
        POSTFOLD_PLEAT_DISPERSE_INPUT,
        POSTFOLD_PLEAT_THRESH_DROP_INPUT,

        INPUTS_LEN
	};
	enum OutputId {
        //sigouts
		MASTER_LEFT_OR_MONO_OUTPUT,
        MASTER_RIGHT_OUTPUT,
        MASTER_PULSE_OUTPUT,
        FIXED_CUSTOM_ONE_LEFT_OR_MONO_OUTPUT,
        FIXED_CUSTOM_ONE_RIGHT_OUTPUT,
        FIXED_CUSTOM_ONE_PULSE_OUTPUT,
        FIXED_CUSTOM_TWO_LEFT_OR_MONO_OUTPUT,
        FIXED_CUSTOM_TWO_RIGHT_OUTPUT,
        FIXED_CUSTOM_TWO_PULSE_OUTPUT,
        FREE_CUSTOM_LEFT_OR_MONO_OUTPUT,
        FREE_CUSTOM_RIGHT_OUTPUT,
        FREE_CUSTOM_PULSE_OUTPUT,
        OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Octoplus() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        //config audio sigins
        configParam(MAIN_PREBIAS_DC_AMP_PARAM, -10, 10, 0, "Main Prebias DC Amp");
        configParam(MAIN_PREBIAS_EXT_GAIN_PARAM, 0, 2, 1, "Main Prebias External Gain");
        configParam(SIDE_PREBIAS_DC_AMP_PARAM, -10, 10, 0, "Side Prebias DC Amp");
        configParam(SIDE_PREBIAS_EXT_GAIN_PARAM, 0, 2, 1, "Side Prebias External Gain");
        
        configParam(PREFOLD_GAIN_PARAM, 0, 1, 1, "Prefold Gain");
        configParam(PREFOLD_OFFSET_PARAM, 0, 10, 5, "Prefold Offset");
        configParam(PREFOLD_DISPERSE_PARAM, 0, 10, 5, "Prefold Disperse");
        configParam(PREFOLD_THRESH_DROP_PARAM, 0, 10, 5, "Prefold Thresh Drop");
        configParam(PREFOLD_CROSS_LENGTH_PARAM, 0, 10, 5, "Prefold Cross Length");

        configParam(PREFOLD_FILTER_CUTOFF_PARAM, 0, 4, 4, "Prefold Filter Cutoff");
        configParam(PREFOLD_FILTER_RESONANCE_PARAM, 0, 1, 0.707, "Prefold Filter Resonance");

        configParam(RECT_GAIN_PARAM, 0, 10, 5, "Rect Gain");
        configParam(RECT_PASSES_PARAM, 0, 10, 5, "Rect Passes");
        configParam(RECT_BLEND_PARAM, 0, 10, 5, "Rect Blend");
        configParam(RECT_STEREO_CROSS_PARAM, 0, 10, 5, "Rect Stereo Cross");

        configParam(RECT_QUANT_TO_MOD_PARAM, 0, 13, 0, "Rect Quant to Mod");
        configParam(RECT_QUANT_ATTR_TO_MOD_PARAM, 0, 13, 0, "Rect Quant Attr to Mod");
        configParam(RECT_QUANT_LISTEN_TO_PARAM, 0, 13, 0, "Rect Quant Listen to");
        configParam(VAR_A_SET_LHS_PARAM, 0, 13, 0, "Var A Set LHS");
        configParam(VAR_A_SET_OP_PARAM, 0, 13, 0, "Var A Set Op");
        configParam(VAR_A_SET_RHS_PARAM, 0, 13, 0, "Var A Set RHS");
        configParam(VAR_B_SET_LHS_PARAM, 0, 13, 0, "Var B Set LHS");
        configParam(VAR_B_SET_OP_PARAM, 0, 13, 0, "Var B Set Op");
        configParam(VAR_B_SET_RHS_PARAM, 0, 13, 0, "Var B Set RHS");
        configParam(COND_1_SET_LHS_PARAM, 0, 13, 0, "Cond 1 Set LHS");
        configParam(COND_1_SET_COMP_PARAM, 0, 7, 0, "Cond 1 Set Bool");
        configParam(COND_1_SET_RHS_PARAM, 0, 13, 0, "Cond 1 Set RHS");
        configParam(COND_2_SET_BOOL_PARAM, 0, 9, 0, "Cond 2 Set Qual");
        configParam(COND_2_SET_LHS_PARAM, 0, 13, 0, "Cond 2 Set LHS");
        configParam(COND_2_SET_COMP_PARAM, 0, 7, 0, "Cond 2 Set Bool");
        configParam(COND_2_SET_RHS_PARAM, 0, 13, 0, "Cond 2 Set RHS");
        configParam(COND_3_SET_BOOL_PARAM, 0, 9, 0, "Cond 3 Set Qual");
        configParam(COND_3_SET_LHS_PARAM, 0, 13, 0, "Cond 3 Set LHS");
        configParam(COND_3_SET_COMP_PARAM, 0, 7, 0, "Cond 3 Set Bool");
        configParam(COND_3_SET_RHS_PARAM, 0, 13, 0, "Cond 3 Set RHS");
        configParam(COND_4_SET_BOOL_PARAM, 0, 9, 0, "Cond 4 Set Qual");
        configParam(COND_4_SET_LHS_PARAM, 0, 13, 0, "Cond 4 Set LHS");
        configParam(COND_4_SET_COMP_PARAM, 0, 7, 0, "Cond 4 Set Bool");
        configParam(COND_4_SET_RHS_PARAM, 0, 13, 0, "Cond 4 Set RHS");

        configParam(SWAP_QUANT_A_B_PARAM, 0, 1, 0, "Swap Exprs A and B");
        configParam(SWAP_COND_1_2_PARAM, 0, 1, 0, "Swap Cond 1 and 2");
        configParam(SWAP_COND_2_3_PARAM, 0, 1, 0, "Swap Cond 2 and 3");
        configParam(SWAP_COND_3_4_PARAM, 0, 1, 0, "Swap Cond 3 and 4");


        //add more here

        configParam(POSTFOLD_GAIN_PARAM, 0, 1, 1, "Postfold Gain");
        configParam(POSTFOLD_OFFSET_PARAM, 0, 10, 5, "Postfold Offset");
        configParam(POSTFOLD_DISPERSE_PARAM, 0, 10, 5, "Postfold Disperse");
        configParam(POSTFOLD_THRESH_DROP_PARAM, 0, 10, 5, "Postfold Thresh Drop");
        configParam(POSTFOLD_CROSS_LENGTH_PARAM, 0, 10, 5, "Postfold Cross Length");

        configParam(POSTFOLD_FILTER_CUTOFF_PARAM, 0, 4, 4, "Postfold Filter Cutoff");
        configParam(POSTFOLD_FILTER_RESONANCE_PARAM, 0, 1, 0.707, "Postfold Filter Resonance");

        configParam(MASTER_OUT_GAIN_PARAM, 0, 10, 5, "Master Gain");
        configParam(MASTER_OUT_PAN_PARAM, 0, 10, 5, "Master Pan");

        configParam(CUSTOM_OUT_ONE_GAIN_PARAM, 0, 10, 5, "Custom Out 1 Gain");
        configParam(CUSTOM_OUT_ONE_PAN_PARAM, 0, 10, 5, "Custom Out 1 Pan");
        configParam(CUSTOM_OUT_ONE_THREE_STATE_M, 0, 2, 0, "Custom Out 1 3State M");
        configParam(CUSTOM_OUT_ONE_THREE_STATE_DM, 0, 2, 0, "Custom Out 1 3State dM");
        configParam(CUSTOM_OUT_ONE_THREE_STATE_D2M, 0, 2, 0, "Custom Out 1 3State d2M");

        configParam(CUSTOM_OUT_TWO_GAIN_PARAM, 0, 10, 5, "Custom Out 2 Gain");
        configParam(CUSTOM_OUT_TWO_PAN_PARAM, 0, 10, 5, "Custom Out 2 Pan");
        configParam(CUSTOM_OUT_TWO_THREE_STATE_M, 0, 2, 0, "Custom Out 2 3State M");
        configParam(CUSTOM_OUT_TWO_THREE_STATE_DM, 0, 2, 0, "Custom Out 2 3State dM");
        configParam(CUSTOM_OUT_TWO_THREE_STATE_D2M, 0, 2, 0, "Custom Out 2 3State d2M");

        configParam(FREE_OUT_GAIN_PARAM, 0, 10, 5, "Free Out Gain");
        configParam(FREE_OUT_PAN_PARAM, 0, 10, 5, "Free Out Pan");
        configParam(FREE_OUT_THREE_STATE_M, 0, 2, 0, "Free Out 3State M");
        configParam(FREE_OUT_THREE_STATE_DM, 0, 2, 0, "Free Out 3State dM");
        configParam(FREE_OUT_THREE_STATE_D2M, 0, 2, 0, "Free Out 3State d2M");

        
        configInput(MAIN_LEFT_OR_MONO_INPUT, "Main L/M");
		configInput(MAIN_RIGHT_INPUT, "Main R");
        configInput(MAIN_PREBIAS_LEFT_OR_MONO_INPUT, "Main Prebias L/M");
		configInput(MAIN_PREBIAS_RIGHT_INPUT, "Main Prebias R");
        configInput(SIDE_LEFT_OR_MONO_INPUT, "Side L/M");
		configInput(SIDE_RIGHT_INPUT, "Side R");
        configInput(SIDE_PREBIAS_LEFT_OR_MONO_INPUT, "Side Prebias L/M");
		configInput(SIDE_PREBIAS_RIGHT_INPUT, "Side Prebias R");
        //config prefold sigins
        configInput(PREFOLD_PLEAT_GAIN_INPUT, "Prefold Gain");
		configInput(PREFOLD_PLEAT_OFFSET_INPUT, "Prefold Offset");
        configInput(PREFOLD_PLEAT_DISPERSE_INPUT, "Prefold Disperse");
		configInput(PREFOLD_PLEAT_THRESH_DROP_INPUT, "Prefold Thresh Drop");


        configInput(RECT_QUANT_GAIN_INPUT, "Rect Gain");
		configInput(RECT_NUM_PASSES_INPUT, "Rect Passes");
        configInput(RECT_CONDITION_BLEND_INPUT, "Rect Blend");

        configInput(POSTFOLD_PLEAT_GAIN_INPUT, "Postfold Gain");
		configInput(POSTFOLD_PLEAT_OFFSET_INPUT, "Postfold Offset");
        configInput(POSTFOLD_PLEAT_DISPERSE_INPUT, "Postfold Disperse");
		configInput(POSTFOLD_PLEAT_THRESH_DROP_INPUT, "Postfold Thresh Drop");
		

        
        configOutput(MASTER_LEFT_OR_MONO_OUTPUT, "Master L/M");
        configOutput(MASTER_RIGHT_OUTPUT, "Master R");
        configOutput(MASTER_PULSE_OUTPUT, "Master Pulse");
        configOutput(FIXED_CUSTOM_ONE_LEFT_OR_MONO_OUTPUT, "Fixed Custom 1 L/M");
        configOutput(FIXED_CUSTOM_ONE_RIGHT_OUTPUT, "Fixed Custom 1 R");
        configOutput(FIXED_CUSTOM_ONE_PULSE_OUTPUT, "Fixed Custom 1 Pulse");
        configOutput(FIXED_CUSTOM_TWO_LEFT_OR_MONO_OUTPUT, "Fixed Custom 2 L/M");
        configOutput(FIXED_CUSTOM_TWO_RIGHT_OUTPUT, "Fixed Custom 2 R");
        configOutput(FIXED_CUSTOM_TWO_PULSE_OUTPUT, "Fixed Custom 2 Pulse");
        configOutput(FREE_CUSTOM_LEFT_OR_MONO_OUTPUT, "Free Custom 1 L/M");
        configOutput(FREE_CUSTOM_RIGHT_OUTPUT, "Free Custom 1 R");
        configOutput(FREE_CUSTOM_PULSE_OUTPUT, "Free Custom 1 Pulse");

        trues[0] = true;
        trues[1] = true;
        trues[2] = true;
        trues[3] = true;
	}
    //Main signal values
    /*double leftOrMonoMainPosCurrent;
    double rightMainPosCurrent;
    double leftOrMonoMainPosPrev;
    double rightMainPosPrev;
    double leftOrMonoMainPos2Prev;
    double rightMainPos2Prev;
    double leftOrMonoMainDeriv;
    double rightMainDeriv;
    double leftOrMonoMainSecDeriv;
    double rightMainSecDeriv;
    //Main prebias signal values
    double leftOrMonoMainPrebiasPos;
    double rightMainPrebiasPos;
    //Side signal values
    double leftOrMonoSidePosCurrent;
    double rightSidePosCurrent;
    double leftOrMonoSidePosPrev;
    double rightSidePosPrev;
    double leftOrMonoSidePos2Prev;
    double rightSidePos2Prev;
    double leftOrMonoSideDeriv;
    double rightSideDeriv;
    double leftOrMonoSideSecDeriv;
    double rightSideSecDeriv;
    //Side prebias signal values
    double leftOrMonoSidePrebiasPos;
    double rightSidePrebiasPos;*/
    
    PolySample leftOrMonoMain;
    PolySample rightMain;
    PolySample leftOrMonoMainPrebias;
    PolySample rightMainPrebias;

    PolySample leftMainTotalPrebias;
    PolySample rightMainTotalPrebias;

    PolySample leftOrMonoSide;
    PolySample rightSide;
    PolySample leftOrMonoSidePrebias;
    PolySample rightSidePrebias;

    PolySample leftMainPrefoldInput;
    PolySample rightMainPrefoldInput;
    PolySample leftSidePrefoldInput;
    PolySample rightSidePrefoldInput;

    PolySample leftFoldOutput;
    PolySample rightFoldOutput;

    FoldUnit preFold;
    FoldUnit postFold;

    

    float gain;
    float thresh;
    float shift;
    float drop;

    bool trues[4];

    PolyFilter prefoldFilter;
    PolyFilter postfoldFilter;
    PolyFilter dcBlocker;

    PolySample leftPrefoldFilterResult;
    PolySample rightPrefoldFilterResult;

    
    PolySample dcBlockFreq;
    PolySample dcBlockRes;

	void process(const ProcessArgs& args) override {
        //shift cached values back
        //TODO: rework with vectors
        
        //capture poly inputs from the main and side + prebs. handles left/mono logic
        leftOrMonoMain.polySampleFromInput(inputs[MAIN_LEFT_OR_MONO_INPUT]);
        if(!inputs[MAIN_RIGHT_INPUT].isConnected() && inputs[MAIN_LEFT_OR_MONO_INPUT].isConnected()){
            rightMain = leftOrMonoMain;
        }
        else{
            rightMain.polySampleFromInput(inputs[MAIN_RIGHT_INPUT]);
        }

        leftOrMonoMainPrebias.polySampleFromInput(inputs[MAIN_PREBIAS_LEFT_OR_MONO_INPUT]);
         if(!inputs[MAIN_PREBIAS_RIGHT_INPUT].isConnected() && inputs[MAIN_PREBIAS_LEFT_OR_MONO_INPUT].isConnected()){
            rightMainPrebias = leftOrMonoMainPrebias;
        }
        else{
            rightMainPrebias.polySampleFromInput(inputs[MAIN_PREBIAS_RIGHT_INPUT]);
        }

        leftOrMonoSide.polySampleFromInput(inputs[MAIN_LEFT_OR_MONO_INPUT]);
        if(!inputs[MAIN_RIGHT_INPUT].isConnected() && inputs[MAIN_LEFT_OR_MONO_INPUT].isConnected()){
            rightSide = leftOrMonoSide;
        }
        else{
            rightSide.polySampleFromInput(inputs[MAIN_RIGHT_INPUT]);
        }

        leftOrMonoSidePrebias.polySampleFromInput(inputs[SIDE_PREBIAS_LEFT_OR_MONO_INPUT]);
         if(!inputs[SIDE_PREBIAS_RIGHT_INPUT].isConnected() && inputs[SIDE_PREBIAS_LEFT_OR_MONO_INPUT].isConnected()){
            rightSidePrebias = leftOrMonoSidePrebias;
        }
        else{
            rightSidePrebias.polySampleFromInput(inputs[SIDE_PREBIAS_RIGHT_INPUT]);
        }
        


        leftMainPrefoldInput = leftOrMonoMain + (params[MAIN_PREBIAS_DC_AMP_PARAM].getValue()) + (leftOrMonoMainPrebias * params[MAIN_PREBIAS_EXT_GAIN_PARAM].getValue());
        rightMainPrefoldInput = rightMain + (params[MAIN_PREBIAS_DC_AMP_PARAM].getValue()) + (rightMainPrebias * params[MAIN_PREBIAS_EXT_GAIN_PARAM].getValue());
        
        leftSidePrefoldInput = leftOrMonoSide + (params[SIDE_PREBIAS_DC_AMP_PARAM].getValue()) + (leftOrMonoSidePrebias * params[SIDE_PREBIAS_EXT_GAIN_PARAM].getValue());
        rightSidePrefoldInput = rightSide + (params[SIDE_PREBIAS_DC_AMP_PARAM].getValue()) + (rightSidePrebias * params[SIDE_PREBIAS_EXT_GAIN_PARAM].getValue());

        
        thresh = 2.f;
        gain = params[PREFOLD_GAIN_PARAM].getValue();
        shift = params[PREFOLD_OFFSET_PARAM].getValue();
        drop = params[PREFOLD_THRESH_DROP_PARAM].getValue();


        leftFoldOutput = preFold.multiFold(leftMainPrefoldInput, thresh, gain, shift, drop, trues);
        rightFoldOutput = preFold.multiFold(rightMainPrefoldInput, thresh, gain, shift, drop, trues);
        //leftFoldOutput = leftMainPrefoldInput;
        //rightFoldOutput = rightMainPrefoldInput;



        //bias compensation?
        //leftFoldOutput = leftFoldOutput - (leftOrMonoMainPrebias * params[MAIN_PREBIAS_EXT_GAIN_PARAM].getValue());
        //rightFoldOutput = rightFoldOutput - (rightMainPrebias * params[MAIN_PREBIAS_EXT_GAIN_PARAM].getValue());

        float rawCutoff = params[PREFOLD_FILTER_CUTOFF_PARAM].getValue(); // repl
        float rawResonance = params[PREFOLD_FILTER_RESONANCE_PARAM].getValue();
        
        //refactor this, it's garbage. cutoff is exponentially mapped here, but resonance is mapped in the method, what a pain
        prefoldFilter.updateParams(2 * pow(10, rawCutoff), rawResonance);
        prefoldFilter.updateDownstreamParams();

        prefoldFilter.updateCoefs_AllTypes(PolyFilterState::LOWPASS_2P);

        leftPrefoldFilterResult = prefoldFilter.process(leftFoldOutput);
        rightPrefoldFilterResult = prefoldFilter.process(rightFoldOutput);

        dcBlockFreq = 15;
        dcBlockRes = sqrt(2) / 2;
        dcBlocker.updateParams(dcBlockFreq, dcBlockRes);
        dcBlocker.updateDownstreamParams();
        dcBlocker.updateCoefs_AllTypes(PolyFilterState::HIGHPASS_2P);
        
        dcBlocker.process(leftPrefoldFilterResult);
        dcBlocker.process(rightPrefoldFilterResult);

        //refactor this trash
        leftPrefoldFilterResult.polySampleToOutput(outputs[MASTER_LEFT_OR_MONO_OUTPUT]);
        rightPrefoldFilterResult.polySampleToOutput(outputs[MASTER_RIGHT_OUTPUT]);

        //DEBUG(leftMainPrefoldInput.toString().c_str());






		/*leftOrMonoMainPos2Prev = leftOrMonoMainPosPrev;
        rightMainPos2Prev = rightMainPosPrev;
        leftOrMonoMainPosPrev = leftOrMonoMainPosCurrent;
        rightMainPosPrev = rightMainPosCurrent;
        leftOrMonoSidePos2Prev = leftOrMonoSidePosPrev;
        rightSidePos2Prev = rightSidePosPrev;
        leftOrMonoSidePosPrev = leftOrMonoSidePosCurrent;
        rightSidePosPrev = rightSidePosCurrent;
        //read main + main prebias inputs
        leftOrMonoMainPosCurrent = inputs[MAIN_LEFT_OR_MONO_INPUT].getVoltage();
        rightMainPosCurrent = inputs[MAIN_RIGHT_INPUT].getVoltage();
        leftOrMonoMainPrebiasPos = inputs[MAIN_PREBIAS_LEFT_OR_MONO_INPUT].getVoltage();
        rightMainPrebiasPos = inputs[MAIN_PREBIAS_RIGHT_INPUT].getVoltage();
        //read side + side prebias inputs
        leftOrMonoSidePosCurrent = inputs[SIDE_LEFT_OR_MONO_INPUT].getVoltage();
        rightSidePosCurrent = inputs[SIDE_RIGHT_INPUT].getVoltage();
        leftOrMonoSidePrebiasPos = inputs[SIDE_PREBIAS_LEFT_OR_MONO_INPUT].getVoltage();*/
        //rightSidePrebiasPos = inputs[SIDE_PREBIAS_RIGHT_INPUT].getVoltage();
        

        
        
        //prefold(double threshold)
            //detect if main and/or side signal passes threshold
            //apply gain to portions outside threshold (pleat)
            //gain shift 
            //energy disperse
            //crossfade
        //rectify()
            //determine mod target
            //calculate A and B
            //evaluate each condition separately
            //PROCESS 1: Simple
            //if the criteria are met, apply gain to main signal
            //EP
            //PROCESS 2: Rate
            //if the criteria are met, apply gain to signal derivative and integrate forward
            //EP
            //stereo blend
        //postfold()
            ////detect if post rect main signal passes threshold
            //apply gain to pleat
            //gain shift 
            //energy disperse
            //crossfade
        //processouts()
            //send main signal to outs
            //evaluate fixed condition and write out if true
            //evaluate variable condition and write out if true
        
	}
};

struct OctoplusWidget : ModuleWidget {
	/*std::vector<std::shared_ptr<Svg>> quantSvgCache;
    std::vector<std::shared_ptr<Svg>> compSvgCache;
    std::vector<std::shared_ptr<Svg>> opSvgCache;
    std::vector<std::shared_ptr<Svg>> boolSvgCache;*/
    
    OctoplusWidget(Octoplus* module) {
        setPanel(createPanel(asset::plugin(pluginInstance, "res/ocenginemule.svg")));
        if(module){setModule(module);

		//setPanel(createPanel(asset::plugin(pluginInstance, "res/ocenginemule.svg")));

		addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        //addChild(createWidget<FoldUnitOscilloscope>(mm2px(Vec(35, 70))));
        //addChild(createWidget<FoldUnitOscilloscope>(mm2px(Vec(135, 70))));

        auto* PrefoldOscilloscope = createWidget<FoldUnitOscilloscope>(mm2px(Vec(35, 70)));
        if(module){PrefoldOscilloscope->setFoldPointer(&(module->preFold));}
        addChild(PrefoldOscilloscope);
        auto* PostfoldOscilloscope = createWidget<FoldUnitOscilloscope>(mm2px(Vec(135, 70)));
        if(module){PostfoldOscilloscope->setFoldPointer(&(module->postFold));}
        addChild(PostfoldOscilloscope);

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10, 40)), module, Octoplus::MAIN_PREBIAS_DC_AMP_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(20, 40)), module, Octoplus::MAIN_PREBIAS_EXT_GAIN_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10, 80)), module, Octoplus::SIDE_PREBIAS_DC_AMP_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(20, 80)), module, Octoplus::SIDE_PREBIAS_EXT_GAIN_PARAM));
        
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 10)), module, Octoplus::PREFOLD_GAIN_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 20)), module, Octoplus::PREFOLD_OFFSET_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 30)), module, Octoplus::PREFOLD_DISPERSE_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 40)), module, Octoplus::PREFOLD_THRESH_DROP_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 50)), module, Octoplus::PREFOLD_CROSS_LENGTH_PARAM));
        
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 120)), module, Octoplus::PREFOLD_FILTER_CUTOFF_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(50, 120)), module, Octoplus::PREFOLD_FILTER_RESONANCE_PARAM));

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(80, 110)), module, Octoplus::RECT_GAIN_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(90, 110)), module, Octoplus::RECT_PASSES_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(100, 110)), module, Octoplus::RECT_BLEND_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(110, 110)), module, Octoplus::RECT_STEREO_CROSS_PARAM));

        //top stuff
        auto* rectQuantToModPtr = createParam<ScrollableDisplay>(mm2px(Vec(85, 5)), module, Octoplus::RECT_QUANT_TO_MOD_PARAM);
        if(module){rectQuantToModPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(rectQuantToModPtr);

        auto* rectQuantAttrToModPtr = createParam<ScrollableDisplay>(mm2px(Vec(95, 5)), module, Octoplus::RECT_QUANT_ATTR_TO_MOD_PARAM);
        if(module){rectQuantAttrToModPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(rectQuantAttrToModPtr);

        auto* rectQuantListenToPtr = createParam<ScrollableDisplay>(mm2px(Vec(105, 5)), module, Octoplus::RECT_QUANT_LISTEN_TO_PARAM);
        if(module){rectQuantListenToPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(rectQuantListenToPtr);

        //var A
        auto* varASetOpParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(75, 15)), module, Octoplus::VAR_A_SET_OP_PARAM);
        if(module){varASetOpParamPtr->setType(ScrollableDisplayType::OP);}
        addParam(varASetOpParamPtr);

        auto* varASetLHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(65, 15)), module, Octoplus::VAR_A_SET_LHS_PARAM);
        if(module){varASetLHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(varASetLHSParamPtr);

        if(module){varASetLHSParamPtr->listener = &varASetOpParamPtr->controller;} //link var A LHS to var A OP

        auto* varASetRHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(85, 15)), module, Octoplus::VAR_A_SET_RHS_PARAM);
        if(module){varASetRHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(varASetRHSParamPtr);

        //var B
        auto* varBSetOpParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(105, 15)), module, Octoplus::VAR_B_SET_OP_PARAM);
        if(module){varBSetOpParamPtr->setType(ScrollableDisplayType::OP);}
        addParam(varBSetOpParamPtr);
        
        auto* varBSetLHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(95, 15)), module, Octoplus::VAR_B_SET_LHS_PARAM);
        if(module){varBSetLHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(varBSetLHSParamPtr);

        varBSetLHSParamPtr->listener = &varBSetOpParamPtr->controller;
        

        auto* varBSetRHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(115, 15)), module, Octoplus::VAR_B_SET_RHS_PARAM);
        if(module){varBSetRHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(varBSetRHSParamPtr);

        //cond 1
        auto* cond1SetLHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(85, 25)), module, Octoplus::COND_1_SET_LHS_PARAM);
        if(module){cond1SetLHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(cond1SetLHSParamPtr);

        auto* cond1SetBoolParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(95, 25)), module, Octoplus::COND_1_SET_COMP_PARAM);
        if(module){cond1SetBoolParamPtr->setType(ScrollableDisplayType::COMP);}
        addParam(cond1SetBoolParamPtr);

        auto* cond1SetRHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(105, 25)), module, Octoplus::COND_1_SET_RHS_PARAM);
        if(module){cond1SetRHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(cond1SetRHSParamPtr);

        //cond 2
        auto* cond2SetQualParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(75, 35)), module, Octoplus::COND_2_SET_BOOL_PARAM);
        if(module){cond2SetQualParamPtr->setType(ScrollableDisplayType::BOOL);}
        addParam(cond2SetQualParamPtr);
        
        auto* cond2SetLHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(85, 35)), module, Octoplus::COND_2_SET_LHS_PARAM);
        if(module){cond2SetLHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(cond2SetLHSParamPtr);

        auto* cond2SetBoolParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(95, 35)), module, Octoplus::COND_2_SET_COMP_PARAM);
        if(module){cond2SetBoolParamPtr->setType(ScrollableDisplayType::COMP);}
        addParam(cond2SetBoolParamPtr);

        auto* cond2SetRHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(105, 35)), module, Octoplus::COND_2_SET_RHS_PARAM);
        if(module){cond2SetRHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(cond2SetRHSParamPtr);

        //cond 3
        auto* cond3SetQualParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(75, 45)), module, Octoplus::COND_3_SET_BOOL_PARAM);
        if(module){cond3SetQualParamPtr->setType(ScrollableDisplayType::BOOL);}
        addParam(cond3SetQualParamPtr);

        auto* cond3SetLHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(85, 45)), module, Octoplus::COND_3_SET_LHS_PARAM);
        if(module){cond3SetLHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(cond3SetLHSParamPtr);

        auto* cond3SetBoolParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(95, 45)), module, Octoplus::COND_3_SET_COMP_PARAM);
        if(module){cond3SetBoolParamPtr->setType(ScrollableDisplayType::COMP);}
        addParam(cond3SetBoolParamPtr);

        auto* cond3SetRHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(105, 45)), module, Octoplus::COND_3_SET_RHS_PARAM);
        if(module){cond3SetRHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(cond3SetRHSParamPtr);

        //cond 4
        auto* cond4SetQualParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(75, 55)), module, Octoplus::COND_4_SET_BOOL_PARAM);
        if(module){cond4SetQualParamPtr->setType(ScrollableDisplayType::BOOL);}
        addParam(cond4SetQualParamPtr);

        auto* cond4SetLHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(85, 55)), module, Octoplus::COND_4_SET_LHS_PARAM);
        if(module){cond4SetLHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(cond4SetLHSParamPtr);

        auto* cond4SetBoolParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(95, 55)), module, Octoplus::COND_4_SET_COMP_PARAM);
        if(module){cond4SetBoolParamPtr->setType(ScrollableDisplayType::COMP);}
        addParam(cond4SetBoolParamPtr);

        auto* cond4SetRHSParamPtr = createParam<ScrollableDisplay>(mm2px(Vec(105, 55)), module, Octoplus::COND_4_SET_RHS_PARAM);
        if(module){cond4SetRHSParamPtr->setType(ScrollableDisplayType::QUANT);}
        addParam(cond4SetRHSParamPtr);

        //swap buttons
        auto* swapQuantA_BButton = createParam<SwapButton>(mm2px(Vec(115, 80)), module, Octoplus::SWAP_QUANT_A_B_PARAM);
        if(module){swapQuantA_BButton->setPtrs(nullptr, module->getParamQuantity(Octoplus::VAR_A_SET_LHS_PARAM),
                                    module->getParamQuantity(Octoplus::VAR_A_SET_OP_PARAM),
                                    module->getParamQuantity(Octoplus::VAR_A_SET_RHS_PARAM),
                                    nullptr, module->getParamQuantity(Octoplus::VAR_B_SET_LHS_PARAM),
                                    module->getParamQuantity(Octoplus::VAR_B_SET_OP_PARAM),
                                    module->getParamQuantity(Octoplus::VAR_B_SET_RHS_PARAM));}
        addParam(swapQuantA_BButton);

        auto* swapCond1_2Button = createParam<SwapButton>(mm2px(Vec(115, 30)), module, Octoplus::SWAP_COND_1_2_PARAM);
        if(module){swapCond1_2Button->setPtrs(nullptr, module->getParamQuantity(Octoplus::COND_1_SET_LHS_PARAM),
                                    module->getParamQuantity(Octoplus::COND_1_SET_COMP_PARAM),
                                    module->getParamQuantity(Octoplus::COND_1_SET_RHS_PARAM),
                                    nullptr, module->getParamQuantity(Octoplus::COND_2_SET_LHS_PARAM),
                                    module->getParamQuantity(Octoplus::COND_2_SET_COMP_PARAM),
                                    module->getParamQuantity(Octoplus::COND_2_SET_RHS_PARAM));}
        addParam(swapCond1_2Button);

        auto* swapCond2_3Button = createParam<SwapButton>(mm2px(Vec(115, 40)), module, Octoplus::SWAP_COND_2_3_PARAM);
        if(module){swapCond2_3Button->setPtrs(module->getParamQuantity(Octoplus::COND_2_SET_BOOL_PARAM), 
                                    module->getParamQuantity(Octoplus::COND_2_SET_LHS_PARAM),
                                    module->getParamQuantity(Octoplus::COND_2_SET_COMP_PARAM),
                                    module->getParamQuantity(Octoplus::COND_2_SET_RHS_PARAM),
                                    module->getParamQuantity(Octoplus::COND_3_SET_BOOL_PARAM), 
                                    module->getParamQuantity(Octoplus::COND_3_SET_LHS_PARAM),
                                    module->getParamQuantity(Octoplus::COND_3_SET_COMP_PARAM),
                                    module->getParamQuantity(Octoplus::COND_3_SET_RHS_PARAM));}
        addParam(swapCond2_3Button);

        auto* swapCond3_4Button = createParam<SwapButton>(mm2px(Vec(115, 50)), module, Octoplus::SWAP_COND_3_4_PARAM);
       if(module){swapCond3_4Button->setPtrs(module->getParamQuantity(Octoplus::COND_3_SET_BOOL_PARAM), 
                                    module->getParamQuantity(Octoplus::COND_3_SET_LHS_PARAM),
                                    module->getParamQuantity(Octoplus::COND_3_SET_COMP_PARAM),
                                    module->getParamQuantity(Octoplus::COND_3_SET_RHS_PARAM),
                                    module->getParamQuantity(Octoplus::COND_4_SET_BOOL_PARAM), 
                                    module->getParamQuantity(Octoplus::COND_4_SET_LHS_PARAM),
                                    module->getParamQuantity(Octoplus::COND_4_SET_COMP_PARAM),
                                    module->getParamQuantity(Octoplus::COND_4_SET_RHS_PARAM));}
        addParam(swapCond3_4Button);


        


        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(140, 10)), module, Octoplus::POSTFOLD_GAIN_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(140, 20)), module, Octoplus::POSTFOLD_OFFSET_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(140, 30)), module, Octoplus::POSTFOLD_DISPERSE_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(140, 40)), module, Octoplus::POSTFOLD_THRESH_DROP_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(140, 50)), module, Octoplus::POSTFOLD_CROSS_LENGTH_PARAM));

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(140, 120)), module, Octoplus::POSTFOLD_FILTER_CUTOFF_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(150, 120)), module, Octoplus::POSTFOLD_FILTER_RESONANCE_PARAM));

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(175, 25)), module, Octoplus::MASTER_OUT_GAIN_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(185, 25)), module, Octoplus::MASTER_OUT_PAN_PARAM));
        
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(175, 50)), module, Octoplus::CUSTOM_OUT_ONE_GAIN_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(185, 50)), module, Octoplus::CUSTOM_OUT_ONE_PAN_PARAM));
        

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(175, 75)), module, Octoplus::CUSTOM_OUT_TWO_GAIN_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(185, 75)), module, Octoplus::CUSTOM_OUT_TWO_PAN_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(175, 100)), module, Octoplus::FREE_OUT_GAIN_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(185, 100)), module, Octoplus::FREE_OUT_PAN_PARAM));

        addParam(createParam<ThreeStateCheckbox>(mm2px(Vec(168, 31)), module, Octoplus::CUSTOM_OUT_ONE_THREE_STATE_M));
        addParam(createParam<ThreeStateCheckbox>(mm2px(Vec(178, 31)), module, Octoplus::CUSTOM_OUT_ONE_THREE_STATE_DM));
        addParam(createParam<ThreeStateCheckbox>(mm2px(Vec(188, 31)), module, Octoplus::CUSTOM_OUT_ONE_THREE_STATE_D2M));

        addParam(createParam<ThreeStateCheckbox>(mm2px(Vec(168, 56)), module, Octoplus::CUSTOM_OUT_TWO_THREE_STATE_M));
        addParam(createParam<ThreeStateCheckbox>(mm2px(Vec(178, 56)), module, Octoplus::CUSTOM_OUT_TWO_THREE_STATE_DM));
        addParam(createParam<ThreeStateCheckbox>(mm2px(Vec(188, 56)), module, Octoplus::CUSTOM_OUT_TWO_THREE_STATE_D2M));

        addParam(createParam<ThreeStateCheckbox>(mm2px(Vec(168, 81)), module, Octoplus::FREE_OUT_THREE_STATE_M));
        addParam(createParam<ThreeStateCheckbox>(mm2px(Vec(178, 81)), module, Octoplus::FREE_OUT_THREE_STATE_DM));
        addParam(createParam<ThreeStateCheckbox>(mm2px(Vec(188, 81)), module, Octoplus::FREE_OUT_THREE_STATE_D2M));
        
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10, 10)), module, Octoplus::MAIN_LEFT_OR_MONO_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20, 10)), module, Octoplus::MAIN_RIGHT_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10, 30)), module, Octoplus::MAIN_PREBIAS_LEFT_OR_MONO_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20, 30)), module, Octoplus::MAIN_PREBIAS_RIGHT_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10, 50)), module, Octoplus::SIDE_LEFT_OR_MONO_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20, 50)), module, Octoplus::SIDE_RIGHT_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10, 70)), module, Octoplus::SIDE_PREBIAS_LEFT_OR_MONO_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20, 70)), module, Octoplus::SIDE_PREBIAS_RIGHT_INPUT));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(50, 10)), module, Octoplus::PREFOLD_PLEAT_GAIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(50, 20)), module, Octoplus::PREFOLD_PLEAT_OFFSET_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(50, 30)), module, Octoplus::PREFOLD_PLEAT_DISPERSE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(50, 40)), module, Octoplus::PREFOLD_PLEAT_THRESH_DROP_INPUT));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(80, 120)), module, Octoplus::RECT_QUANT_GAIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(90, 120)), module, Octoplus::RECT_NUM_PASSES_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(100, 120)), module, Octoplus::RECT_CONDITION_BLEND_INPUT));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(150, 10)), module, Octoplus::POSTFOLD_PLEAT_GAIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(150, 20)), module, Octoplus::POSTFOLD_PLEAT_OFFSET_INPUT));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(150, 30)), module, Octoplus::POSTFOLD_PLEAT_DISPERSE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(150, 40)), module, Octoplus::POSTFOLD_PLEAT_THRESH_DROP_INPUT));
		

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(170, 15)), module, Octoplus::MASTER_LEFT_OR_MONO_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(180, 15)), module, Octoplus::MASTER_RIGHT_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(190, 15)), module, Octoplus::MASTER_PULSE_OUTPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(170, 40)), module, Octoplus::FIXED_CUSTOM_ONE_LEFT_OR_MONO_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(180, 40)), module, Octoplus::FIXED_CUSTOM_ONE_RIGHT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(190, 40)), module, Octoplus::FIXED_CUSTOM_ONE_PULSE_OUTPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(170, 65)), module, Octoplus::FIXED_CUSTOM_TWO_LEFT_OR_MONO_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(180, 65)), module, Octoplus::FIXED_CUSTOM_TWO_RIGHT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(190, 65)), module, Octoplus::FIXED_CUSTOM_TWO_PULSE_OUTPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(170, 90)), module, Octoplus::FREE_CUSTOM_LEFT_OR_MONO_OUTPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(180, 90)), module, Octoplus::FREE_CUSTOM_RIGHT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(190, 90)), module, Octoplus::FREE_CUSTOM_PULSE_OUTPUT));}

        
	}
};


Model* modelOctoplus = createModel<Octoplus, OctoplusWidget>("octoplus");