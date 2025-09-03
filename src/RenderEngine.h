#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#pragma once
#include "IRenderer.h"
#include "MapRenderer.h"
#include "SatelliteRenderer.h"
#include <vector>

#include <memory>

class RenderEngine {
public:
  RenderEngine(std::unique_ptr<IRenderer> renderer);

  void renderFrame(int width, int height, const std::vector<GPSPosition>& satellitePositions);

private:
  std::unique_ptr<IRenderer> renderer;
  MapRenderer mapRenderer;
  SatelliteRenderer satelliteRenderer;
};


#endif // RENDERENGINE_H

