#pragma once
#include "PolySample.hpp"

enum class PolyLiterals{
    ZEROES,
    ONES,
    ASCENDING_0S,
    ASCENDING_1S,
    DESCENDING_0S,
    DESCENDING_1S,
    ALTERN_UNIP,
    ALTERN_BIP,

    //interleaving masks
    ITL_1_ON_1,
    ITL_2_ON_1,
    ITL_1_ON_2,
    ITL_2_ON_2,

    ITL_1_ON_3,
    ITL_2_ON_3,
    ITL_3_ON_1,
    ITL_3_ON_2,
    ITL_3_ON_3,

    ITL_4_ON_1,
    ITL_4_ON_2,
    ITL_4_ON_3,
    ITL_1_ON_4,
    ITL_2_ON_4,
    ITL_3_ON_4,
    ITL_4_ON_4,
    
    /*ITL_5_ON_1,
    ITL_5_ON_2,
    ITL_5_ON_3,
    ITL_5_ON_4,

    ITL_*/
    LITERS_LEN
};

enum class PolyOperations{
    SHIFT,
    MUL,
    INTERLEAVE,
    ROTATE,
    INTERPOLATE,
    OPERS_LEN
};

inline PolySample getPolyLiteral(PolyLiterals lit){
    switch(lit){
        case PolyLiterals::ZEROES:
            return PolySample(0.f);
        case PolyLiterals::ONES:
            return PolySample(1.f);
        case PolyLiterals::ASCENDING_0S:
            return PolySample(0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
        case PolyLiterals::ASCENDING_1S:
            return PolySample(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        case PolyLiterals::DESCENDING_0S:
            return PolySample(15.f, 14.f, 13.f, 12.f, 11.f, 10.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f);
        case PolyLiterals::DESCENDING_1S:
            return PolySample(16.f, 15.f, 14.f, 13.f, 12.f, 11.f, 10.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f);
        case PolyLiterals::ALTERN_UNIP:
            return PolySample(1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f);
        case PolyLiterals::ALTERN_BIP:
            return PolySample(1.f, -1.f, 1.f, -1.f, 1.f, -1.f, 1.f, -1.f, 1.f, -1.f, 1.f, -1.f, 1.f, -1.f, 1.f, -1.f);

        case PolyLiterals::ITL_1_ON_1:
            return PolySample(1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f);
        case PolyLiterals::ITL_2_ON_1:
            return PolySample(1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f);
        case PolyLiterals::ITL_1_ON_2:
            return PolySample(1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f);
        case PolyLiterals::ITL_2_ON_2:
            return PolySample(1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f);
        default:
            return PolySample(0.f); 
    }
}

inline PolySample getPolyOperation(PolySample lhs, PolySample rhs, PolySample itl, PolyOperations op){
    switch(op){
        case PolyOperations::SHIFT:
            return lhs + rhs;
        case PolyOperations::MUL:
            return lhs * rhs;
        case PolyOperations::INTERLEAVE:
            return PolySample::ifelse(lhs, rhs, itl);
        case PolyOperations::ROTATE:
            return PolySample::voiceRotate(lhs, (int)rhs[0]);
        case PolyOperations::INTERPOLATE:
            return itl[0] * lhs + (1 - itl[0]) * rhs;
    }
}