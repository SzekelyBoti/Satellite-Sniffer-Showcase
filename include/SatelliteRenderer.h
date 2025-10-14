#ifndef SATELLITETRACKER_SATELLITERENDERER_H
#define SATELLITETRACKER_SATELLITERENDERER_H

#pragma once
#include "GPSPosition.h"
#include "IRenderer.h"
#include "SatelliteIcon.h"
#include <vector>

// Handles rendering of satellite icons on the map using a provided IRenderer.
class SatelliteRenderer {
public:
    // Constructor: takes a renderer to draw satellites with
    explicit SatelliteRenderer(IRenderer* renderer);
    ~SatelliteRenderer() = default;

    // Loads the satellite icon image into a texture
    // Returns true on success, false if loading fails
    bool loadSatellite(const SatelliteIcon& icon);

    // Renders all satellites at their GPS positions
    // positions: list of satellite positions
    // width, height: dimensions of the rendering area
    void render(const std::vector<GPSPosition>& positions, int width, int height);

private:
    IRenderer* renderer = nullptr;   // Renderer used for drawing
    void* satelliteTexture = nullptr; // Texture of the satellite icon
};


#endif // SATELLITETRACKER_SATELLITERENDERER_H
