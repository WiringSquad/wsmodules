#pragma once
#include "plugin.hpp"
#include "PolySample.hpp"
#include "PolySampleBuffer.hpp"
#include "ScrollableDisplay.hpp"

struct RectUnit{
    PolySample gain;
    PolySample cond1Mask;
    PolySample cond2Mask;
    PolySample cond3Mask;
    PolySample cond4Mask;
    PolySample condSerialMask;

    PolySample quantMain;
    PolySample quantSide;
    PolySample mainDeriv;
    PolySample mainSecondDeriv;
    PolySample sideDeriv;
    PolySample sideSecondDeriv;

    PolySample quantA;
    PolySample quantB;
    PolySample quantADeriv;
    PolySample quantASecondDeriv;
    PolySample quantBDeriv;
    PolySample quantBSecondDeriv;
    

    PolySampleBuffer mainDerivBuffer;
    PolySampleBuffer sideDerivBuffer;
    PolySampleBuffer quantADerivBuffer;
    PolySampleBuffer quantBDerivBuffer;

    float passes;
    float rate;

    RectUnit(){
        mainDerivBuffer = PolySampleBuffer(2);
        sideDerivBuffer = PolySampleBuffer(2);
        quantADerivBuffer = PolySampleBuffer(2);
        quantBDerivBuffer = PolySampleBuffer(2);
    }
    
    PolySample generateMask(){

    }
    
    void updateMasks(){

    }
    
    PolySample getQuant(ScrollerData::QuantsData q){
        switch(q){
            case ScrollerData::M:
                return quantMain;
                break;
            case ScrollerData::dM:
                return mainDeriv;
                break;
            case ScrollerData::d2M:
                return mainSecondDeriv;
                break;
            case ScrollerData::S:
                return quantSide;
                break;
            case ScrollerData::dS:
                return sideDeriv;
                break;
            case ScrollerData::d2S:
                return sideSecondDeriv;
                break;
            case ScrollerData::A:
                return quantA; 
                break;
            case ScrollerData::dA:
                return quantADeriv;
                break;
            case ScrollerData::d2A:         
                return quantASecondDeriv;
                break;
            case ScrollerData::B:
                return quantB;
                break;
            case ScrollerData::dB:
                return quantBDeriv;
                break;
            case ScrollerData::d2B:
                return quantBSecondDeriv;
                break;
            default:
                return PolySample(0.0f); // or throw an error
                break;
        }
    }

    PolySample getOp(PolySample lhs, ScrollerData::OpsData op, PolySample rhs){
        switch(op){
            case ScrollerData::PLUS:
                return lhs + rhs;
            case ScrollerData::MINUS:
                return lhs - rhs;
            case ScrollerData::MUL:
                return lhs * rhs;
            case ScrollerData::DIV:
                return lhs / rhs;
            case ScrollerData::POWER:
                return PolySample::pow(lhs, rhs); //update def
            case ScrollerData::BALOGB:
                return PolySample(); // add this
            case ScrollerData::SIN:
                return PolySample::sin(rhs);
            case ScrollerData::COS:
                return PolySample::cos(rhs);
            case ScrollerData::TAN:
                return PolySample::tan(rhs);
            case ScrollerData::ISIN:
                return PolySample::ifelse(lhs, PolySample(1.0f), PolySample(0.0f));
            case ScrollerData::ICOS:
                return PolySample::ifelse(lhs, PolySample(1.0f), PolySample(0.0f));
            case ScrollerData::ITAN:
                return PolySample::atan(rhs);
            default:
                return PolySample(0.0f); // or throw an error
        }
    }

    PolySample getComp(PolySample lhs, ScrollerData::CompsData comp, PolySample rhs){
        switch(comp){
            case ScrollerData::EQ:
                return lhs == rhs;
            case ScrollerData::NEQ:
                return lhs != rhs;
            case ScrollerData::GT:
                return lhs > rhs;
            case ScrollerData::LT:
                return lhs < rhs;
            case ScrollerData::GTE:
                return lhs >= rhs;
            case ScrollerData::LTE:
                return lhs <= rhs;
            default:    
                return PolySample(0.0f); 
        }
    }

    PolySample getBool(PolySample lhs, ScrollerData::BoolsData boolOp, PolySample rhs){
        switch(boolOp){
            case ScrollerData::AND:
                return lhs & rhs;
            case ScrollerData::OR:
                return lhs | rhs;
            case ScrollerData::UNL: 
                return PolySample::unless(lhs, rhs);
            case ScrollerData::NND:
                return PolySample::nand(lhs, rhs);
            case ScrollerData::NOR:
                return PolySample::nor(lhs, rhs);
            case ScrollerData::XOR:
                return lhs ^ rhs;
            case ScrollerData::XNR:
                return PolySample::xnor(lhs, rhs);
            case ScrollerData::IMP:
                return PolySample::imply(lhs, rhs); 
            default:
                return PolySample(0.0f);
        }
    }
    
    PolySample singleRect(PolySample sam, PolySample gain, PolySample mask){
        return PolySample::ifelse(mask, sam * gain, sam);
    }

    PolySample singlePassSerial(PolySample sam){
        PolySample maskPipeline = getBool(cond1Mask, ScrollerData::AND, cond2Mask);
        maskPipeline = getBool(maskPipeline, ScrollerData::AND, cond3Mask);
        maskPipeline = getBool(maskPipeline, ScrollerData::AND, cond4Mask);

        return singleRect(sam, gain, maskPipeline);
    }

    PolySample singlePassParallel(PolySample sam){
        PolySample rect1 = singleRect(sam, gain, cond1Mask);
        PolySample rect2 = singleRect(sam, gain, cond2Mask);
        PolySample rect3 = singleRect(sam, gain, cond3Mask);
        PolySample rect4 = singleRect(sam, gain, cond4Mask);

        return (rect1 + rect2 + rect3 + rect4) / 4;
    }

    PolySample multiPass(PolySample sam){
        PolySample pipeline = PolySample();
        PolySample pipeline_1ago;
        int roundedPasses = static_cast<int>(floor(passes));
        float blend = static_cast<int>(passes - floor(passes));

        for(int i = 0; i < roundedPasses + 1; i++){
            pipeline_1ago = pipeline;
            pipeline = true ? singlePassSerial(sam) : singlePassParallel(sam);
        }

        return PolySample::crossfade(pipeline_1ago, pipeline, blend);
    }

    PolySample process(PolySample mainSam, PolySample sideSam){
        //set all quants properly
        mainDeriv = PolySample::naive_bfd(mainDerivBuffer[1], mainSam, 1 / rate);
        sideDeriv = PolySample::naive_bfd(sideDerivBuffer[1], sideSam, 1 / rate);
        mainSecondDeriv = PolySample::naive_second_order_bfd(mainDerivBuffer[0], mainDerivBuffer[1], mainSam, 1 / rate);
        sideSecondDeriv = PolySample::naive_second_order_bfd(sideDerivBuffer[0], sideDerivBuffer[1], sideSam, 1 / rate);

        quantA = getOp(getQuant(ScrollerData::M), ScrollerData::PLUS, ScrollerData::S);
        quantB = getOp(getQuant(ScrollerData::M), ScrollerData::PLUS, ScrollerData::S);
        quantADeriv = PolySample::naive_bfd(quantADerivBuffer[1], quantA, 1 / rate);
        quantBDeriv = PolySample::naive_bfd(quantBDerivBuffer[1], quantB, 1 / rate);
        quantASecondDeriv = PolySample::naive_second_order_bfd(quantADerivBuffer[0], quantADerivBuffer[1], quantA, 1 / rate);
        quantBSecondDeriv = PolySample::naive_second_order_bfd(quantBDerivBuffer[0], quantBDerivBuffer[1], quantB, 1 / rate);
        
        cond1Mask = getComp(getQuant(ScrollerData::M), ScrollerData::EQ, getQuant(ScrollerData::M));
        cond2Mask = getComp(getQuant(ScrollerData::M), ScrollerData::EQ, getQuant(ScrollerData::M));
        cond3Mask = getComp(getQuant(ScrollerData::M), ScrollerData::EQ, getQuant(ScrollerData::M));
        cond4Mask = getComp(getQuant(ScrollerData::M), ScrollerData::EQ, getQuant(ScrollerData::M));

        return multiPass(mainSam);        
    }
};