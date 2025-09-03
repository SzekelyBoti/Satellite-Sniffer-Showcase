#ifndef SATELLITETRACKER_SATELLITERENDERER_H
#define SATELLITETRACKER_SATELLITERENDERER_H

#pragma once
#include <vector>
#include "IRenderer.h"
#include "GPSPosition.h"

class SatelliteRenderer {
public:
    explicit SatelliteRenderer(IRenderer* renderer);
    ~SatelliteRenderer() = default;

    void render(const std::vector<GPSPosition>& positions, int width, int height);

private:
    IRenderer* renderer = nullptr;
};


#endif // SATELLITETRACKER_SATELLITERENDERER_H
