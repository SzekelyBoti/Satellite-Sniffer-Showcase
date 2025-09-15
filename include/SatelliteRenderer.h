#ifndef SATELLITETRACKER_SATELLITERENDERER_H
#define SATELLITETRACKER_SATELLITERENDERER_H

#pragma once
#include "GPSPosition.h"
#include "IRenderer.h"
#include "SatelliteIcon.h"
#include <vector>

class SatelliteRenderer {
public:
    explicit SatelliteRenderer(IRenderer* renderer);
    ~SatelliteRenderer() = default;
    bool loadSatellite(const SatelliteIcon& icon);

    void render(const std::vector<GPSPosition>& positions, int width, int height);

private:
    IRenderer* renderer = nullptr;
    void* satelliteTexture = nullptr;
};


#endif // SATELLITETRACKER_SATELLITERENDERER_H
