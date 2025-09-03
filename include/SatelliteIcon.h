#pragma once
#include "IRenderer.h"
#include "GPSPosition.h"

class SatelliteIcon {
public:
    SatelliteIcon();
    ~SatelliteIcon();
    void render(IRenderer* renderer, const GPSPosition& position);
};