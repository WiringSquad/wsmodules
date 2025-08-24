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
    simd::float_4 vec = (clampedIndex < 4) ? chans0_3 : (clampedIndex < 8) ? chans4_7 : (clampedIndex < 12) ? chans8_11 : chans12_15;
    return vec[index % 4];
}

const float& PolySample::operator[](size_t index) const{
    int clampedIndex = rack::clamp((int)index, 0, 15);
    simd::float_4 vec = (clampedIndex < 4) ? chans0_3 : (clampedIndex < 8) ? chans4_7 : (clampedIndex < 12) ? chans8_11 : chans12_15;
    return vec[index % 4];
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

