#include "EarthMap.h"

/**
 * @brief Constructs an EarthMap from a given image file.
 * @param file Path to the map image.
 */
EarthMap::EarthMap(const std::string& file)
    : RenderableAsset(file) {}

/**
 * @brief Sets the zoom level of the Earth map.
 * @param z Zoom factor (e.g., 1.0 = normal, 2.0 = double size).
 */
void EarthMap::setZoom(float z) {
  zoomLevel = z;
}

/**
 * @brief Returns the current zoom level of the Earth map.
 * @return Zoom factor.
 */
float EarthMap::getZoom() const {
  return zoomLevel;
}

