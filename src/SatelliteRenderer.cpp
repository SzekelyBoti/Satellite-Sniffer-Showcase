#include "SatelliteRenderer.h"

SatelliteRenderer::SatelliteRenderer(IRenderer* renderer)
    : renderer(renderer) {}

void SatelliteRenderer::render(const std::vector<GPSPosition>& positions, int width, int height) {
  for (const auto& pos : positions) {
    int x = static_cast<int>((pos.getLongitude() + 180.0) / 360.0 * width);
    int y = static_cast<int>((90.0 - pos.getLatitude()) / 180.0 * height);
    renderer->drawPoint(x, y);
  }
}
