#pragma once
#include "plugin.hpp"


struct PolySample {
    simd::float_4 chans0_3;
    simd::float_4 chans4_7;
    simd::float_4 chans8_11;
    simd::float_4 chans12_15;
    //float temp[16];

    // 16 samples for polyphonic input
    static constexpr float EPS = 0.0001f;

    //void setSample(Input inp); deprecated but still here

    PolySample();

    PolySample(float inp);

    PolySample(float c0, float c1, float c2, float c3,
               float c4, float c5, float c6, float c7,
               float c8, float c9, float c10, float c11,
               float c12, float c13, float c14, float c15);

    std::string toString();
    
    static void polySampleFromInput(PolySample& p, Input& inp);

    static void polySampleToOutput(const PolySample& p, Output& otp);
    
    PolySample& operator=(const float& value);
    
    PolySample& operator=(const PolySample& other);

    //optimization for the math: 
    //lots of adding of zeros. make an int to keep track of the number of channels active.
    //if a math op encounters a zero, it ignores it and increments a counter. 
    //if the counter hits the number of active channels, the operation ends automatically, and values are just copied over.
    //only update the number of active channels after an op that can turn zero values nonzero.
    
    PolySample operator+(const float& value) const;
    
    PolySample operator+(const PolySample& other) const;

    friend PolySample operator+(const float& value, const PolySample& other);

    PolySample operator +=(const float& value);

    PolySample operator +=(const PolySample& other);

    PolySample& operator++();

    PolySample operator++(int);



    PolySample operator-(const float& value) const;
    
    PolySample operator-(const PolySample& other) const;

    friend PolySample operator-(const float& value, const PolySample& other);

    PolySample operator-=(const float& value);

    PolySample operator-=(const PolySample& other);

    PolySample& operator--();

    PolySample operator--(int);

    PolySample operator-();


    
    PolySample operator*(const float& value) const;
    
    PolySample operator*(const PolySample& other) const;

    friend PolySample operator*(const float& value, const PolySample& other);

    PolySample operator*=(const float& value);

    PolySample operator*=(const PolySample& other);



    PolySample operator/(const float& value) const;

    PolySample operator/(const PolySample& other) const;

    friend PolySample operator/(const float& value, const PolySample& other);

    PolySample operator/=(const float& value);

    PolySample operator/=(const PolySample& other);



    PolySample operator>=(const PolySample& other) const;

    PolySample operator<=(const PolySample& other) const;

    float& operator[](size_t index);

    const float& operator[](size_t index) const;

    //TODO: add simd math funcs
    //add conversions to and from float[16] just in case

    static PolySample sin(PolySample arg);

    static PolySample cos(PolySample arg);

    static PolySample tan(PolySample arg);

    static PolySample asin(PolySample arg);

    static PolySample acos(PolySample arg);

    static PolySample atan(PolySample arg);

    static PolySample pow(PolySample arg, float p);

    static PolySample pow(float arg, PolySample p);

    static PolySample pow(PolySample arg, PolySample p);

    static PolySample exp(PolySample arg);

    static PolySample sinc(float pos); //sinc for ideal resampling. float represents the time
    
    //backwards finite difference
    static PolySample naive_bfd(PolySample lastSample, PolySample currentSample, float betwTime);

    //second order backwards finite difference
    static PolySample naive_second_order_bfd(PolySample twoSamplesAgo, PolySample lastSample, PolySample currentSample, float betwTime);

    static PolySample ifelse(PolySample mask, PolySample a, PolySample b);

    static PolySample crossfade(PolySample a, PolySample b, PolySample p);

    static PolySample crossfade(PolySample a, PolySample b, float p);

    static void mac(PolySample& acc, float a, float b);

    static void mac(PolySample& acc, PolySample a, float b);

    static void mac(PolySample& acc, float a, PolySample b);
    
    static void mac(PolySample& acc, PolySample a, PolySample b);

    PolySample operator&(const PolySample& other) const;

    PolySample operator|(const PolySample& other) const;

    PolySample operator~() const; 

    PolySample operator^(const PolySample& other) const;

    static PolySample unless(PolySample a, PolySample b);

    static PolySample nand(PolySample a, PolySample b);

    static PolySample nor(PolySample a, PolySample b);

    static PolySample xnor(PolySample a, PolySample b);

    static PolySample imply(PolySample a, PolySample b);

    PolySample operator==(const PolySample& other) const;

    PolySample operator!=(const PolySample& other) const;

    PolySample operator>(const PolySample& other) const;

    PolySample operator<(const PolySample& other) const;

    static PolySample collapse(const PolySample& other, int* totalVoices);

    static PolySample sqrt(float radicand);

    static PolySample sqrt(PolySample radicand);

    static PolySample abs(PolySample arg);

    static PolySample log(PolySample arg);

    static PolySample log_arb(PolySample arg, PolySample base);

    static PolySample log2(PolySample arg);

    static PolySample log10(PolySample arg);

    static PolySample linear_to_db(PolySample lin);

    static PolySample db_to_linear(PolySample db);

    static PolySample db_scale(PolySample arg, PolySample scale);

    static void pan_triangular(PolySample left,  PolySample right, PolySample& leftOut, PolySample& rightOut, PolySample pan); 

    static void pan_circular(PolySample left,  PolySample right, PolySample& leftOut, PolySample& rightOut, PolySample pan);

    static void lr_to_ms(PolySample left, PolySample right, PolySample& mid, PolySample& side);

    static void ms_to_lr(PolySample mid, PolySample side, PolySample& left, PolySample& right);

    static uint16_t movemask(PolySample expr);
    
    bool contains(float val);

    bool containsNans();

    

    
    
    static PolySample voiceRotateLeft(PolySample p, uint16_t rot);

    static PolySample voiceRotateRight(PolySample p, uint16_t rot);

    static PolySample voiceRotate(PolySample p, int rot);

    //bool operator==(const PolySample& other);

    

    
    

    
    
};

