#include "PolySample.hpp"
#include "PolyFilter.hpp"

enum class ParallelPolyFilterState{

};

struct ParallelPolyFilter : PolyFilter{
    std::vector<PolyFilter*> parallel;

    PolySample process(PolySample currentX) override{
        PolySample pipeline;
        for(float i = 0.f; i < parallel.size(); i += 1.f){
            pipeline = pipeline + parallel.at(i)->process(currentX);
        }
        return pipeline / parallel.size();
    }
};