#pragma once
#include "RenderableAsset.h"

// Represents a map of the Earth that can be rendered and zoomed
class EarthMap : public RenderableAsset {
public:
    EarthMap() = default;

    // Constructs an Earth map from a given image file
    explicit EarthMap(const std::string& file);

    // Sets the zoom level of the map
    void setZoom(float z);

    // Returns the current zoom level
    float getZoom() const;

private:
    float zoomLevel = 1.0f;  // Zoom factor (1.0 = default)
};
