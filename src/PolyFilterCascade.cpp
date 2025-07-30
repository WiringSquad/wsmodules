#include "PolySample.hpp"
#include "PolyFilter.hpp"

struct PolyFilterCascade{
    std::vector<PolyFilter> cascade;

    PolySample process(PolySample sam){
        PolySample pipeline = sam;
        for(int i = 0; i < cascade.size(); i++){
            pipeline = cascade.at(i).process(pipeline);
        }
        return pipeline;
    }

    //more here!
};