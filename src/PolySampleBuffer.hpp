#pragma once
#include "plugin.hpp"
#include "PolySample.hpp"

struct PolySampleBuffer{
    int maxSize = 0;
    std::deque<PolySample> polyBuffer;
    
    PolySampleBuffer();

    PolySampleBuffer(int mS);
    
    void pushNewSample(PolySample ps);

    PolySample naiveBFD(float betwTime);

    PolySample naiveSecondOrderBFD(float betwTime);

    PolySample& operator[](size_t index);

    const PolySample& operator[](size_t index) const;

    /*PolySample& operator[](float index);

    const PolySample& operator[](float index) const;*/

    const PolySample resample(float index) const;

    const PolySampleBuffer& operator=(const PolySampleBuffer& other);
};

//stats tools, add sort, min and max

void sort(PolySampleBuffer& buf);

PolySampleBuffer sort(const PolySampleBuffer& buf);

PolySample min(const PolySampleBuffer& buf);

PolySample max(const PolySampleBuffer& buf);

PolySample mean(const PolySampleBuffer& buf);

PolySample median(const PolySampleBuffer& buf);

PolySample variance(const PolySampleBuffer& buf);

PolySample stddev(const PolySampleBuffer& buf);

PolySample rms(const PolySampleBuffer& buf);

PolySample skew(const PolySampleBuffer& buf);

//add clear and fill utilities





