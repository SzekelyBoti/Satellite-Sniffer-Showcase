#include "MapRenderer.h"
#include <iostream>

MapRenderer::MapRenderer(IRenderer* renderer)
    : renderer(renderer) {}

bool MapRenderer::loadMap(const std::string& filename) {
  if (mapTexture) {
    renderer->destroyTexture(mapTexture);
    mapTexture = nullptr;
  }

  mapTexture = renderer->loadTexture(filename);
  if (!mapTexture) {
    std::cerr << "Failed to load map texture: " << filename << "\n";
    return false;
  }
  return true;
}

void MapRenderer::render(int width, int height) {
  if (mapTexture) {
    renderer->drawTexture(mapTexture, 0, 0, width, height);
  }
}



