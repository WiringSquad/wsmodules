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

PolySample::PolySample(float c0, float c1, float c2, float c3,
                       float c4, float c5, float c6, float c7,
                       float c8, float c9, float c10, float c11,
                       float c12, float c13, float c14, float c15){
    chans0_3 = simd::float_4(c0, c1, c2, c3);
    chans4_7 = simd::float_4(c4, c5, c6, c7);
    chans8_11 = simd::float_4(c8, c9, c10, c11);
    chans12_15 = simd::float_4(c12, c13, c14, c15);
}

std::string PolySample::toString(){
    std::string temp = "";
    for(int i = 0; i < 16; i++){
        temp += std::to_string((*this)[i]) + (i != 15 ? ", " : "");
    }
    return temp;
}

void PolySample::polySampleFromInput(PolySample& p, Input& inp){
    //inp.readVoltages(temp);
    p.chans0_3 = inp.getVoltageSimd<simd::float_4>(0);
    p.chans4_7 = inp.getVoltageSimd<simd::float_4>(4);
    p.chans8_11 = inp.getVoltageSimd<simd::float_4>(8);
    p.chans12_15 = inp.getVoltageSimd<simd::float_4>(12);
}

void PolySample::polySampleToOutput(const PolySample& p, Output& otp){
    otp.setChannels(16);
    otp.setVoltageSimd<simd::float_4>(p.chans0_3, 0);
    otp.setVoltageSimd<simd::float_4>(p.chans4_7, 4);
    otp.setVoltageSimd<simd::float_4>(p.chans8_11, 8);
    otp.setVoltageSimd<simd::float_4>(p.chans12_15, 12);
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

PolySample operator+(const float& value, const PolySample& other){
    PolySample result;
    result.chans0_3 = value + other.chans0_3;
    result.chans4_7 = value + other.chans4_7;
    result.chans8_11 = value + other.chans8_11;
    result.chans12_15 = value + other.chans12_15;
    return result;
}

PolySample PolySample::operator+=(const float& value){
    chans0_3 += value;
    chans4_7 += value;
    chans8_11 += value;
    chans12_15 += value;
    return *this;
}

PolySample PolySample::operator+=(const PolySample& other){
    chans0_3 += other.chans0_3;
    chans4_7 += other.chans4_7;
    chans8_11 += other.chans8_11;
    chans12_15 += other.chans12_15;
    return *this;
}

PolySample& PolySample::operator++(){
    chans0_3 += 1.f;
    chans4_7 += 1.f;
    chans8_11 += 1.f;
    chans12_15 += 1.f;
    return *this;
}

PolySample PolySample::operator++(int){
    PolySample temp = *this;
    ++(*this);
    return temp;
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

PolySample operator-(const float& value, const PolySample& other){
    PolySample result;
    result.chans0_3 = value - other.chans0_3;
    result.chans4_7 = value - other.chans4_7;
    result.chans8_11 = value - other.chans8_11;
    result.chans12_15 = value - other.chans12_15;
    return result;
}

PolySample PolySample::operator-=(const float& value){
    chans0_3 -= value;
    chans4_7 -= value;
    chans8_11 -= value;
    chans12_15 -= value;
    return *this;
}

PolySample PolySample::operator-=(const PolySample& other){
    chans0_3 -= other.chans0_3;
    chans4_7 -= other.chans4_7;
    chans8_11 -= other.chans8_11;
    chans12_15 -= other.chans12_15;
    return *this;
}

PolySample& PolySample::operator--(){
    chans0_3 -= 1.f;
    chans4_7 -= 1.f;
    chans8_11 -= 1.f;
    chans12_15 -= 1.f;
    return *this;
}

PolySample PolySample::operator--(int){
    PolySample temp = *this;
    --(*this);
    return temp;
}

PolySample PolySample::operator-(){
    PolySample result;
    result.chans0_3 = -this->chans0_3;
    result.chans4_7 = -this->chans4_7;
    result.chans8_11 = -this->chans8_11;
    result.chans12_15 = -this->chans12_15;
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

PolySample operator*(const float& value, const PolySample& other){
    return other * value; 
}

PolySample PolySample::operator*=(const float& value){
    chans0_3 *= value;
    chans4_7 *= value;
    chans8_11 *= value;
    chans12_15 *= value;
    return *this;
}

PolySample PolySample::operator*=(const PolySample& other){
    chans0_3 *= other.chans0_3;
    chans4_7 *= other.chans4_7;
    chans8_11 *= other.chans8_11;
    chans12_15 *= other.chans12_15;
    return *this;
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

PolySample operator/(const float& value, const PolySample& other){
    PolySample result;
    result.chans0_3 = value / other.chans0_3;
    result.chans4_7 = value / other.chans4_7;
    result.chans8_11 = value / other.chans8_11;
    result.chans12_15 = value / other.chans12_15;
    return result;
}

PolySample PolySample::operator/=(const float& value){
    chans0_3 /= value;
    chans4_7 /= value;
    chans8_11 /= value;
    chans12_15 /= value;
    return *this;
}

PolySample PolySample::operator/=(const PolySample& other){
    chans0_3 /= other.chans0_3;
    chans4_7 /= other.chans4_7;
    chans8_11 /= other.chans8_11;
    chans12_15 /= other.chans12_15;
    return *this;
}

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

float& PolySample::operator[](size_t index){
    int clampedIndex = rack::clamp((int)index, 0, 15);
    if(clampedIndex < 4){
        return chans0_3[clampedIndex];
    }
    else if(clampedIndex < 8){
        return chans4_7[clampedIndex - 4];
    }
    else if(clampedIndex < 12){
        return chans8_11[clampedIndex - 8];
    }
    else{
        return chans12_15[clampedIndex - 12];
    }
}

const float& PolySample::operator[](size_t index) const{
    int clampedIndex = rack::clamp((int)index, 0, 15);
    if(clampedIndex < 4){
        return chans0_3[clampedIndex];
    }
    else if(clampedIndex < 8){
        return chans4_7[clampedIndex - 4];
    }
    else if(clampedIndex < 12){
        return chans8_11[clampedIndex - 8];
    }
    else{
        return chans12_15[clampedIndex - 12];
    }
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

PolySample PolySample::pow(float arg, PolySample p){
    PolySample result;
    result.chans0_3 = simd::pow(arg, p.chans0_3);
    result.chans4_7 = simd::pow(arg, p.chans4_7);
    result.chans8_11 = simd::pow(arg, p.chans8_11);
    result.chans12_15 = simd::pow(arg, p.chans12_15);
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

PolySample PolySample::sinc(float pos){
    PolySample polyPos = PolySample(pos);
    return (fabs(pos) < EPS) ? 1 : PolySample::sin(polyPos) / polyPos;
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

void PolySample::mac(PolySample& acc, float a, float b){
    acc.chans0_3 += a * b;
    acc.chans4_7 += a * b;
    acc.chans8_11 += a * b;
    acc.chans12_15 += a * b;
}

void PolySample::mac(PolySample& acc, PolySample a, float b){
    acc.chans0_3 += a.chans0_3 * b;
    acc.chans4_7 += a.chans4_7 * b;
    acc.chans8_11 += a.chans8_11 * b;
    acc.chans12_15 += a.chans12_15 * b;
}

void PolySample::mac(PolySample& acc, float a, PolySample b){
    acc.chans0_3 += a * b.chans0_3;
    acc.chans4_7 += a * b.chans4_7;
    acc.chans8_11 += a * b.chans8_11;
    acc.chans12_15 += a * b.chans12_15;
}

void PolySample::mac(PolySample& acc, PolySample a, PolySample b){
    acc.chans0_3 += a.chans0_3 * b.chans0_3;
    acc.chans4_7 += a.chans4_7 * b.chans4_7;
    acc.chans8_11 += a.chans8_11 * b.chans8_11;
    acc.chans12_15 += a.chans12_15 * b.chans12_15;
}

PolySample PolySample::operator&(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = this->chans0_3 & other.chans0_3;
    result.chans4_7 = this->chans4_7 & other.chans4_7;
    result.chans8_11 = this->chans8_11 & other.chans8_11;
    result.chans12_15 = this->chans12_15 & other.chans12_15;
    return result;
}

PolySample PolySample::operator|(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = this->chans0_3 | other.chans0_3;
    result.chans4_7 = this->chans4_7 | other.chans4_7;
    result.chans8_11 = this->chans8_11 | other.chans8_11;
    result.chans12_15 = this->chans12_15 | other.chans12_15;
    return result;
}

PolySample PolySample::operator^(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = this->chans0_3 ^ other.chans0_3;
    result.chans4_7 = this->chans4_7 ^ other.chans4_7;
    result.chans8_11 = this->chans8_11 ^ other.chans8_11;
    result.chans12_15 = this->chans12_15 ^ other.chans12_15;
    return result;
}

PolySample PolySample::operator~() const {
    PolySample result;
    result.chans0_3 = ~this->chans0_3;
    result.chans4_7 = ~this->chans4_7;
    result.chans8_11 = ~this->chans8_11;
    result.chans12_15 = ~this->chans12_15;
    return result;
}

PolySample PolySample::unless(PolySample a, PolySample b){
    return a & ~b;
}

PolySample PolySample::nand(PolySample a, PolySample b){
    return ~(a & b);
}

PolySample PolySample::nor(PolySample a, PolySample b){
    return ~(a | b);
}

PolySample PolySample::xnor(PolySample a, PolySample b){
    return ~(a ^ b);
}

PolySample PolySample::imply(PolySample a, PolySample b){
    return a | ~b;
}

PolySample PolySample::operator==(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = (this->chans0_3 == other.chans0_3);
    result.chans4_7 = (this->chans4_7 == other.chans4_7);
    result.chans8_11 = (this->chans8_11 == other.chans8_11);
    result.chans12_15 = (this->chans12_15 == other.chans12_15);
    return result;
}

PolySample PolySample::operator!=(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = (this->chans0_3 != other.chans0_3);
    result.chans4_7 = (this->chans4_7 != other.chans4_7);
    result.chans8_11 = (this->chans8_11 != other.chans8_11);
    result.chans12_15 = (this->chans12_15 != other.chans12_15);
    return result;
}

PolySample PolySample::operator>(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = (this->chans0_3 > other.chans0_3);
    result.chans4_7 = (this->chans4_7 > other.chans4_7);
    result.chans8_11 = (this->chans8_11 > other.chans8_11);
    result.chans12_15 = (this->chans12_15 > other.chans12_15);
    return result;
}

PolySample PolySample::operator<(const PolySample& other) const {
    PolySample result;
    result.chans0_3 = (this->chans0_3 < other.chans0_3);
    result.chans4_7 = (this->chans4_7 < other.chans4_7);
    result.chans8_11 = (this->chans8_11 < other.chans8_11);
    result.chans12_15 = (this->chans12_15 < other.chans12_15);
    return result;
}


//pass nullptr in if you don't want to count the voices
PolySample PolySample::collapse(const PolySample& otp, int* totalVoices){
    PolySample result;
    int voicesFound = 0;
    for(int i = 0; i < 16; i++){
        if(fabs(otp[i]) > EPS){
            result[voicesFound++] = otp[i];
        }
    }
    if(totalVoices){*totalVoices = voicesFound;}
    return result;
}

PolySample PolySample::sqrt(float radicand){
    PolySample result;
    result.chans0_3 = simd::sqrt(radicand);
    result.chans4_7 = simd::sqrt(radicand);
    result.chans8_11 = simd::sqrt(radicand);
    result.chans12_15 = simd::sqrt(radicand);
    return result;
}

PolySample PolySample::sqrt(PolySample radicand){
    PolySample result;
    result.chans0_3 = simd::sqrt(radicand.chans0_3);
    result.chans4_7 = simd::sqrt(radicand.chans4_7);
    result.chans8_11 = simd::sqrt(radicand.chans8_11);
    result.chans12_15 = simd::sqrt(radicand.chans12_15);
    return result;
}

PolySample PolySample::abs(PolySample arg){
    PolySample result;
    result.chans0_3 = simd::abs(arg.chans0_3);
    result.chans4_7 = simd::abs(arg.chans4_7);
    result.chans8_11 = simd::abs(arg.chans8_11);
    result.chans12_15 = simd::abs(arg.chans12_15);
    return result;
}

PolySample PolySample::log(PolySample arg){
    PolySample result;
    result.chans0_3 = simd::log(arg.chans0_3);
    result.chans4_7 = simd::log(arg.chans4_7);
    result.chans8_11 = simd::log(arg.chans8_11);
    result.chans12_15 = simd::log(arg.chans12_15);
    return result;
}

PolySample PolySample::log10(PolySample arg){
    PolySample result;
    result.chans0_3 = simd::log10(arg.chans0_3);
    result.chans4_7 = simd::log10(arg.chans4_7);
    result.chans8_11 = simd::log10(arg.chans8_11);
    result.chans12_15 = simd::log10(arg.chans12_15);
    return result;
}

PolySample PolySample::log2(PolySample arg){
    PolySample result;
    result.chans0_3 = simd::log2(arg.chans0_3);
    result.chans4_7 = simd::log2(arg.chans4_7);
    result.chans8_11 = simd::log2(arg.chans8_11);
    result.chans12_15 = simd::log2(arg.chans12_15);
    return result;
}

PolySample PolySample::log_arb(PolySample arg, PolySample base){
    return PolySample::log(arg) / PolySample::log(base);
}

PolySample PolySample::linear_to_db(PolySample lin){
    return 20 * PolySample::log10(lin / 10);
}

PolySample PolySample::db_to_linear(PolySample db){
    return 10 * PolySample::pow(10, db / 20);
}

PolySample PolySample::db_scale(PolySample arg, PolySample db){
    return arg * db_to_linear(db);
}

void PolySample::pan_triangular(PolySample left, PolySample right, PolySample& leftOut, PolySample& rightOut, PolySample pan){
    leftOut *= 1 - pan;
    rightOut *= pan;
}

void PolySample::pan_circular(PolySample left, PolySample right, PolySample& leftOut, PolySample& rightOut, PolySample pan){
    leftOut *= (2/sqrtf(3)) * PolySample::sqrt(1 - PolySample::pow(left, 2));
    rightOut *= (2/sqrtf(3)) * PolySample::sqrt((2*right) - PolySample::pow(right, 2));
}

void PolySample::lr_to_ms(PolySample left, PolySample right, PolySample& midOut, PolySample& sideOut){
    midOut = (left + right) * 0.5f;
    sideOut = (left - right) * 0.5f;
}

void PolySample::ms_to_lr(PolySample mid, PolySample side, PolySample& leftOut, PolySample& rightOut){
    leftOut = mid + side;
    rightOut = mid - side;
}

uint16_t PolySample::movemask(PolySample expr){
    uint16_t m1 = simd::movemask(expr.chans0_3);
    uint16_t m2 = simd::movemask(expr.chans4_7);
    uint16_t m3 = simd::movemask(expr.chans8_11);
    uint16_t m4 = simd::movemask(expr.chans12_15);
    return (m1 << 12) | (m2 << 8) | (m3 << 4) | m4;
}

bool PolySample::contains(float val){
    return PolySample::movemask(*this == val) > 0;
}

bool PolySample::containsNans(){
    return PolySample::movemask(*this == *this) != 0xffff;
}

PolySample PolySample::voiceRotateLeft(PolySample p, uint16_t rot){
    float a[rot];
    for(int i = 0; i < rot; i++){
        a[i] = p[i];
    }
    for(int i = 0; i < rot; i++){
        p[i] = p[i + rot];
    }
    for(int i = 0; i < rot; i++){
        p[i + 16 - rot] = a[i];
    }
    return p;
}

PolySample PolySample::voiceRotateRight(PolySample p, uint16_t rot){
    PolySample result = p;
    float a[rot];
    for(int i = 0; i < rot; i++){
        a[i] = result[i + 16 - rot];
    }
    for(int i = 15; i > rot; i--){
        result[i] = result[i - rot];
    }
    for(int i = 0; i < rot; i++){
        result[i] = a[i];
    }
    return result;
}

PolySample PolySample::voiceRotate(PolySample p, int rot){
    rot %= 16;
    if(rot > 0 && rot < 8){
        return voiceRotateRight(p, rot);
    }
    else if(rot >= 8 && rot < 16){
        return voiceRotateLeft(p, rot - 8);
    }
    else if(rot < 0 && rot > -8){
        return voiceRotateLeft(p, -rot);
    }
    else if(rot <= -8 && rot > -16){
        return voiceRotateRight(p, -8 - rot);
    }
    else{
        return p;
    }
}





/*bool PolySample::operator==(const PolySample& other){
    return PolySample::movemask(*this == other) == 0xffff;
}*/


