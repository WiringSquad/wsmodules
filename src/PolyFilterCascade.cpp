#include "PolySample.hpp"
#include "PolyFilter.hpp"

enum class PolyFilterCascadeType{
    
};

struct PolyFilterCascade : PolyFilter{
    std::vector<PolyFilter*> cascade;

   /* PolySample process(PolySample sam){
        PolySample pipeline = sam;
        for(int i = 0; i < cascade.size(); i++){
            pipeline = cascade.at(i).process(pipeline);
        }
        return pipeline;
    }*/
   
    PolySample process(PolySample currentX) override{
        PolySample pipeline;
        for(auto filter : cascade){
            pipeline = filter->process(currentX);
        }
    }
    //more here!
};