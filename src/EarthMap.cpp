#include "EarthMap.h"

EarthMap::EarthMap(const std::string& file)
    : RenderableAsset(file) {}

void EarthMap::setZoom(float z) {
  zoomLevel = z;
}

float EarthMap::getZoom() const {
  return zoomLevel;
}

