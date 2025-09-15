#include "SatelliteRenderer.h"
#include "SatelliteIcon.h"
#include <iostream>

SatelliteRenderer::SatelliteRenderer(IRenderer* renderer)
    : renderer(renderer) {}

bool SatelliteRenderer::loadSatellite(const SatelliteIcon& icon) {
  if (satelliteTexture) {
    renderer->destroyTexture(satelliteTexture);
    satelliteTexture = nullptr;
  }

  satelliteTexture = renderer->loadTexture(icon.getFile());
  if (!satelliteTexture) {
    std::cerr << "Failed to load map texture: " << icon.getFile() << "\n";
    return false;
  }
  return true;
}

void SatelliteRenderer::render(const std::vector<GPSPosition>& positions, int width, int height) {
  for (const auto& pos : positions) {
    int x = static_cast<int>((pos.getLongitude() + 180.0) / 360.0 * width);
    int y = static_cast<int>((90.0 - pos.getLatitude()) / 180.0 * height);
    if (satelliteTexture) {
      renderer->drawTexture(satelliteTexture, x, y, 100 , 100);
    }
  }
}