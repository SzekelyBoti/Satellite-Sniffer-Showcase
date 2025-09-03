#pragma once
#include <memory>

#include "EarthMap.h"
#include "IRenderer.h"
#include "MapRenderer.h"
#include "Satellite.h"
#include "SatelliteRenderer.h"

class RenderEngine {
private:
    IRenderer* renderer;
    MapRenderer* mapRenderer;
    SatelliteRenderer* satelliteRenderer;

public:
    RenderEngine(IRenderer* renderer);
    ~RenderEngine();
    void renderFrame(EarthMap* map, const std::vector<Satellite*>& satellites);
};
