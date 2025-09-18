#pragma once
#include "RenderableAsset.h"

class EarthMap : public RenderableAsset {
public:
    EarthMap() = default;
    explicit EarthMap(const std::string& file);

    void setZoom(float z);
    float getZoom() const;

private:
    float zoomLevel = 1.0f;
};
