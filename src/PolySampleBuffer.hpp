#include "plugin.hpp"

struct PolySampleBuffer{
    int maxSize = 0;
    std::deque<PolySample> polyBuffer;
    
    PolySampleBuffer();

    PolySampleBuffer(int mS);
    
    void pushNewSample(PolySample ps);

    PolySample naiveBFD(float betwTime);

    PolySample naiveSecondOrderBFD(float betwTime);
};