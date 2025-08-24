#include "PolyFilter.hpp"

PolyFilter::PolyFilter(){
    xt = PolySampleBuffer(2);
    yt = PolySampleBuffer(2);
    fs = 48000;
}

PolyFilter::PolyFilter(PolyFilterState pfState, int sampleRate) : fs(sampleRate){
    xt = PolySampleBuffer(2);
    yt = PolySampleBuffer(2);

}

PolyFilter::PolyFilter(PolyFilterState state, PolySample co, PolySample reso, int sampleRate) : state(state), fs(sampleRate){
    xt = PolySampleBuffer(2);
    yt = PolySampleBuffer(2);
    updateParams(co, reso);
    updateDownstreamParams();

}

void PolyFilter::setNonlinearityState(PolyFilterNonlinearityState distState){
    nlState = distState;
}

void PolyFilter::setState(PolyFilterState state){
    state = state;
}

void PolyFilter::setAllStates(PolyFilterState filterState, PolyFilterNonlinearityState distState){
    state = filterState;
    nlState = distState;
}

void PolyFilter::setSampleRate(int sampleRate){
    fs = sampleRate;
}

void PolyFilter::updateCoefs(float A1, float A2, float B0, float B1, float B2){
    a1 = A1;
    a2 = A2;
    b0 = B0;
    b1 = B1;
    b2 = B2;
}

void PolyFilter::updateCoefs(PolySample A0, PolySample A1, PolySample A2, PolySample B0, PolySample B1, PolySample B2){
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
    Q = reso*(qmax - qmin) + qmin;
    //add in q here later
}

void PolyFilter::updateParams(PolySample co, PolySample reso){
    co = 2 * PolySample::pow(10, co);
    omega0 = (co / fs)*2*M_PI;
    float qmin = 0.5;
    float qmax = 20;
    Q = reso*(qmax - qmin) + qmin;
    
}

void PolyFilter::updateDownstreamParams(){
    cos_omega0 = PolySample::cos(omega0);
    sin_omega0 = PolySample::sin(omega0);
    alpha = sin_omega0 / (Q * 2);
    //alpha_1p = omega0 / (omega0 + fs);
    alpha_1p = PolySample::exp(-omega0);
    alpha_1p_hpf = 1 - PolySample::exp(-omega0);
    big_A = PolySample::pow(10, PolySample(gain) / 40); //from the cookbook
}

void PolyFilter::updateCoefs_AllTypes(PolySample co, PolySample reso){    
    updateParams(co, reso);
    updateDownstreamParams();
    switch(state)
    {
    case PolyFilterState::UNITY:
        updateCoefs(1, 0, 0, 1, 0, 0);
        break;
    
    case PolyFilterState::LOWPASS_1P:
        updateCoefs(0, (-alpha_1p), 0, (alpha_1p) - 1, 0, 0); 
        break;
    
    case PolyFilterState::HIGHPASS_1P:
        updateCoefs(0, (-alpha_1p), 0, 1, -1, 0); 
        break;
    
    case PolyFilterState::LOWPASS_2P:
        updateCoefsNormalized(alpha + 1, -2 * cos_omega0, 1 - alpha, ((1 - cos_omega0) / 2), (1 - cos_omega0), ((1 - cos_omega0) / 2)); 
        break;
    
    case PolyFilterState::HIGHPASS_2P:
        updateCoefsNormalized(alpha + 1, cos_omega0 * -2, 1 - alpha, (cos_omega0 + 1) / 2, -1 - cos_omega0, (cos_omega0 + 1) / 2); 
        break;
    
    case PolyFilterState::BANDPASS:
        updateCoefsNormalized(alpha + 1, cos_omega0 * -2, 1 - alpha, Q * alpha, 0, Q * -alpha); 
        break;
    
    case PolyFilterState::NOTCH:
        updateCoefsNormalized(alpha + 1, cos_omega0 * -2, 1 - alpha, 1, cos_omega0 * -2, 1);
        break;
    
    case PolyFilterState::ALLPASS:
        updateCoefsNormalized(alpha + 1, cos_omega0 * -2, 1 - alpha, 1 - alpha, cos_omega0 * -2, alpha + 1);
        break;

    case PolyFilterState::PEAKING:
        updateCoefsNormalized((alpha / big_A) + 1, cos_omega0*-2, ((alpha / big_A)*-1) + 1, (alpha * big_A) + 1, cos_omega0*-1, ((alpha * big_A)*-1) + 1);
        break;
    
    case PolyFilterState::LOWSHELF:
        updateCoefsNormalized(0, 0, 0, 0, 0, 0);
        break;
    
    case PolyFilterState::HIGHSHELF:
        updateCoefsNormalized(0, 0, 0, 0, 0, 0);
        break;
    
    default:
        break;
    }
}

PolySample PolyFilter::process(PolySample currentX){
    PolySample newY;
    newY = (b0 * currentX) + (b1 * xt[1]) + (b2 * xt[0]) - (a1 * yt[1]) - (a2 * yt[0]);
    xt.pushNewSample(currentX);
    yt.pushNewSample(processNonlinearity(newY));
    return newY;
}

PolySample PolyFilter::processNonlinearity(PolySample fbToProcess){
    switch(nlState){
        case PolyFilterNonlinearityState::SC_ITN:
            return PolySample::atan(fbToProcess);
        case PolyFilterNonlinearityState::SC_SGM:
            return PolySample(); //implement this
        case PolyFilterNonlinearityState::IO_RM:
            return PolySample(); //implement this
        default:
            return fbToProcess;
    }
}

