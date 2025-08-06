#pragma once
#include <rack.hpp>
//#include "/Users/rushilnarang/vcv-master/Rack-SDK/include/rack.hpp"


using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;
extern Model* modelOctoplus;
extern Model* modelPolySignalUtility;

extern std::vector<std::shared_ptr<Svg>> quantSvgCache;
extern std::vector<std::shared_ptr<Svg>> compSvgCache;
extern std::vector<std::shared_ptr<Svg>> opSvgCache;
extern std::vector<std::shared_ptr<Svg>> boolSvgCache;

// Declare each Model, defined in each module source file
// extern Model* modelMyModule;
