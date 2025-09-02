#include "EarthMap.h"

EarthMap::EarthMap() : zoomLevel(0.0f) {}
EarthMap::~EarthMap() {}
void EarthMap::load(const std::string& filename) {}
float EarthMap::getZoom() const { return zoomLevel; }