#include "PolySample.hpp"

PolySample::PolySample(){
    chans0_3 = 0.f;
    chans4_7 = 0.f;
    chans8_11 = 0.f;
    chans12_15 = 0.f;
}

PolySample::PolySample(float inp){
    chans0_3 = inp;
    chans4_7 = inp;
    chans8_11 = inp;
    chans12_15 = inp;
}

std::string PolySample::toString(){
    return "";
}

void PolySample::polySampleFromInput(Input& inp){
    //inp.readVoltages(temp);
    chans0_3 = inp.getVoltageSimd<simd::float_4>(0);
    chans4_7 = inp.getVoltageSimd<simd::float_4>(4);
    chans8_11 = inp.getVoltageSimd<simd::float_4>(8);
    chans12_15 = inp.getVoltageSimd<simd::float_4>(12);
}

void PolySample::polySampleToOutput(Output& otp){
    otp.setChannels(16);
    otp.setVoltageSimd<simd::float_4>(chans0_3, 0);
    otp.setVoltageSimd<simd::float_4>(chans4_7, 4);
    otp.setVoltageSimd<simd::float_4>(chans8_11, 8);
    otp.setVoltageSimd<simd::float_4>(chans12_15, 12);
}

PolySample& PolySample::operator=(const float& value){
    chans0_3 = value;
    chans4_7 = value;
    chans8_11 = value;
    chans12_15 = value;
    return *this;
}

PolySample& PolySample::operator=(const PolySample& other){
    chans0_3 = other.chans0_3;
    chans4_7 = other.chans4_7;
    chans8_11 = other.chans8_11;
    chans12_15 = other.chans12_15;
    return *this;
}

PolySample PolySample::operator+(const float& value) const {
    PolySample result;
    result.chans0_3 = this->chans0_3 + value;
    result.chans4_7 = this->chans4_7 + value;
    result.chans8_11 = this->chans8_11 + value;
    result.chans12_15 = this->chans12_15 + value;
    return result;
}

PolySample PolySample::operator+(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = this->chans0_3 + other.chans0_3;
    result.chans4_7 = this->chans4_7 + other.chans4_7;
    result.chans8_11 = this->chans8_11 + other.chans8_11;
    result.chans12_15 = this->chans12_15 + other.chans12_15;
    return result;
}
PolySample PolySample::operator-(const float& value) const{
    PolySample result;
    result.chans0_3 = this->chans0_3 - value;
    result.chans4_7 = this->chans4_7 - value;
    result.chans8_11 = this->chans8_11 - value;
    result.chans12_15 = this->chans12_15 - value;
    return result;
}

PolySample PolySample::operator-(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = this->chans0_3 - other.chans0_3;
    result.chans4_7 = this->chans4_7 - other.chans4_7;
    result.chans8_11 = this->chans8_11 - other.chans8_11;
    result.chans12_15 = this->chans12_15 - other.chans12_15;
    return result;
}

PolySample PolySample::operator*(const float& value) const{
    PolySample result;
    result.chans0_3 = this->chans0_3 * value;
    result.chans4_7 = this->chans4_7 * value;
    result.chans8_11 = this->chans8_11 * value;
    result.chans12_15 = this->chans12_15 * value;
    return result;
}

PolySample PolySample::operator*(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = this->chans0_3 * other.chans0_3;
    result.chans4_7 = this->chans4_7 * other.chans4_7;
    result.chans8_11 = this->chans8_11 * other.chans8_11;
    result.chans12_15 = this->chans12_15 * other.chans12_15;
    return result;
}

PolySample PolySample::operator/(const float& value) const {
    PolySample result;
    result.chans0_3 = this->chans0_3 / value;
    result.chans4_7 = this->chans4_7 / value;
    result.chans8_11 = this->chans8_11 / value;
    result.chans12_15 = this->chans12_15 / value;
    return result;
}

PolySample PolySample::operator/(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = this->chans0_3 / other.chans0_3;
    result.chans4_7 = this->chans4_7 / other.chans4_7;
    result.chans8_11 = this->chans8_11 / other.chans8_11;
    result.chans12_15 = this->chans12_15 / other.chans12_15;
    return result;
}


//this shit is garbage, replace it with an actual deep simd implementation
PolySample PolySample::operator>=(const PolySample& other) const{
    PolySample result;
    result.chans0_3 = (this->chans0_3 >= other.chans0_3);
    result.chans4_7 = (this->chans4_7 >= other.chans4_7);
    result.chans8_11 = (this->chans8_11 >= other.chans8_11);
    result.chans12_15 = (this->chans12_15 >= other.chans12_15);
    return result;
}

PolySample PolySample::operator<=(const PolySample& other) const{
    PolySample result;
    result.chans0_3 = (this->chans0_3 <= other.chans0_3);
    result.chans4_7 = (this->chans4_7 <= other.chans4_7);
    result.chans8_11 = (this->chans8_11 <= other.chans8_11);
    result.chans12_15 = (this->chans12_15 <= other.chans12_15);
    return result;
}



PolySample PolySample::sin(PolySample arg){
    PolySample result;
    result.chans0_3 = simd::sin(arg.chans0_3);
    result.chans4_7 = simd::sin(arg.chans4_7);
    result.chans8_11 = simd::sin(arg.chans8_11);
    result.chans12_15 = simd::sin(arg.chans12_15);
    return result;
}

PolySample PolySample::cos(PolySample arg){
    PolySample result;
    result.chans0_3 = simd::cos(arg.chans0_3);
    result.chans4_7 = simd::cos(arg.chans4_7);
    result.chans8_11 = simd::cos(arg.chans8_11);
    result.chans12_15 = simd::cos(arg.chans12_15);
    return result;
}

PolySample PolySample::tan(PolySample arg){
    PolySample result;
    result.chans0_3 = simd::tan(arg.chans0_3);
    result.chans4_7 = simd::tan(arg.chans4_7);
    result.chans8_11 = simd::tan(arg.chans8_11);
    result.chans12_15 = simd::tan(arg.chans12_15);
    return result;
}

PolySample PolySample::atan(PolySample arg){
    PolySample result;
    result.chans0_3 = simd::atan(arg.chans0_3);
    result.chans4_7 = simd::atan(arg.chans4_7);
    result.chans8_11 = simd::atan(arg.chans8_11);
    result.chans12_15 = simd::atan(arg.chans12_15);
    return result;;
}

PolySample PolySample::pow(PolySample arg, float p){
    PolySample result;
    result.chans0_3 = simd::pow(arg.chans0_3, p);
    result.chans4_7 = simd::pow(arg.chans4_7, p);
    result.chans8_11 = simd::pow(arg.chans8_11, p);
    result.chans12_15 = simd::pow(arg.chans12_15, p);
    return result;
}

PolySample PolySample::pow(PolySample arg, PolySample p){
    PolySample result;
    result.chans0_3 = simd::pow(arg.chans0_3, p.chans0_3);
    result.chans4_7 = simd::pow(arg.chans4_7, p.chans4_7);
    result.chans8_11 = simd::pow(arg.chans8_11, p.chans8_11);
    result.chans12_15 = simd::pow(arg.chans12_15, p.chans12_15);
    return result;
}

PolySample PolySample::exp(PolySample arg){
    PolySample result;
    result.chans0_3 = simd::exp(arg.chans0_3);
    result.chans4_7 = simd::exp(arg.chans4_7);
    result.chans8_11 = simd::exp(arg.chans8_11);
    result.chans12_15 = simd::exp(arg.chans12_15);
    return result;
}


//backwards finite difference
PolySample PolySample::naive_bfd(PolySample lastSample, PolySample currentSample, float betwTime){
    return (currentSample - lastSample) / betwTime;
}

//second order backwards finite difference
PolySample PolySample::naive_second_order_bfd(PolySample twoSamplesAgo, PolySample lastSample, PolySample currentSample, float betwTime){
    return (currentSample - ((lastSample)*2) + twoSamplesAgo) / (betwTime * betwTime);
}

PolySample PolySample::ifelse(PolySample mask, PolySample a, PolySample b){
    PolySample ps;
    ps.chans0_3 = simd::ifelse(mask.chans0_3, a.chans0_3, b.chans0_3);
    ps.chans4_7 = simd::ifelse(mask.chans4_7, a.chans4_7, b.chans4_7);
    ps.chans8_11 = simd::ifelse(mask.chans8_11, a.chans8_11, b.chans8_11);
    ps.chans12_15 = simd::ifelse(mask.chans12_15, a.chans12_15, b.chans12_15);
    return ps;
    
}

PolySample PolySample::crossfade(PolySample a, PolySample b, PolySample p){
    PolySample result;
    result.chans0_3 = simd::crossfade(a.chans0_3, b.chans0_3, p.chans0_3);
    result.chans4_7 = simd::crossfade(a.chans4_7, b.chans4_7, p.chans4_7);
    result.chans8_11 = simd::crossfade(a.chans8_11, b.chans8_11, p.chans8_11);
    result.chans12_15 = simd::crossfade(a.chans12_15, b.chans12_15, p.chans12_15);
    return result;
}

PolySample PolySample::crossfade(PolySample a, PolySample b, float p){
    PolySample result;
    PolySample pSample(p);
    result.chans0_3 = simd::crossfade(a.chans0_3, b.chans0_3, pSample.chans0_3);
    result.chans4_7 = simd::crossfade(a.chans4_7, b.chans4_7, pSample.chans4_7);
    result.chans8_11 = simd::crossfade(a.chans8_11, b.chans8_11, pSample.chans8_11);
    result.chans12_15 = simd::crossfade(a.chans12_15, b.chans12_15, pSample.chans12_15);
    return result;
}


