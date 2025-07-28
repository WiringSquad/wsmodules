#include "PolyFilter.hpp"


PolyFilter::PolyFilter(){
    xt = PolySampleBuffer(2);
    yt = PolySampleBuffer(2);
    fs = 48000;
}

void PolyFilter::updateCoefs(float A1, float A2, float B0, float B1, float B2){
    a1 = A1;
    a2 = A2;
    b0 = B0;
    b1 = B1;
    b2 = B2;
}

void PolyFilter::updateCoefs(PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2){
    a1 = A1;
    a2 = A2;
    b0 = B0;
    b1 = B1;
    b2 = B2;
}

void PolyFilter::updateCoefsNormalized(PolySample A0, PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2){
    a1 = A1 / A0;
    a2 = A2 / A0;
    b0 = B0 / A0;
    b1 = B1 / A0;
    b2 = B2 / A0;
}

void PolyFilter::updateParams(float co, float reso){
    omega0 = 2*M_PI*(co / fs);
    float qmin = 0.5;
    float qmax = 20;
    PolySample temp = (qmax / qmin);
    Q = reso*(qmax - qmin) + qmin;
    //add in q here later
}

void PolyFilter::updateParams(PolySample co, PolySample reso){
    omega0 = (co / fs)*2*M_PI;
    float qmin = 0.5;
    float qmax = 20;
    Q = reso*(qmax - qmin) + qmin;
    
}

void PolyFilter::updateDownstreamParams(){
    cos_omega0 = PolySample::cos(omega0);
    sin_omega0 = PolySample::sin(omega0);
    alpha = sin_omega0 / (Q * 2);
}

void PolyFilter::updateCoefs_AllTypes(PolyFilterState pfState){
    switch (pfState)
    {
    case PolyFilterState::LOWPASS:
        updateCoefsNormalized(alpha + 1, cos_omega0 * -2, (alpha*-1) + 1, (((cos_omega0*-1) + 1) / 2), (cos_omega0*-1) + 1, (((cos_omega0*-1) + 1) / 2)); 
        break;
    
    case PolyFilterState::HIGHPASS:
        updateCoefsNormalized(alpha + 1, cos_omega0 * -2, (alpha*-1) + 1, (cos_omega0 + 1) / 2, (cos_omega0 + 1) * -1, (cos_omega0 + 1) / 2); 
        break;
    
    case PolyFilterState::BANDPASS:
        updateCoefsNormalized(alpha + 1, cos_omega0 * -2, (alpha*-1) + 1, Q * alpha, 0, Q * alpha * -1); 
        break;
    
    case PolyFilterState::NOTCH:
        updateCoefsNormalized(alpha + 1, cos_omega0 * -2, (alpha*-1) + 1, 1, cos_omega0 * -2, 1);
        break;
    
    case PolyFilterState::ALLPASS:
        updateCoefsNormalized(alpha + 1, cos_omega0 * -2, (alpha*-1) + 1, (alpha*-1) + 1, cos_omega0 * -2, alpha + 1);
        break;
    
    default:
        break;
    }
}

PolySample PolyFilter::process(PolySample currentX){
    PolySample newY;
    newY = (b0 * currentX) + (b1 * xt[1]) + (b2 * xt[0]) - (a1 * yt[1]) - (a2 * yt[0]);
    xt.pushNewSample(currentX);
    yt.pushNewSample(newY);
    return newY;
}

