#include "MapRenderer.h"
#include <iostream>

MapRenderer::MapRenderer(IRenderer* renderer)
    : renderer(renderer) {}

bool MapRenderer::loadMap(const EarthMap& map) {
  if (mapTexture) {
    renderer->destroyTexture(mapTexture);
    mapTexture = nullptr;
  }

  mapTexture = renderer->loadTexture(map.getFile());
  if (!mapTexture) {
    std::cerr << "Failed to load map texture: " << map.getFile() << "\n";
    return false;
  }
  return true;
}

void MapRenderer::render(int width, int height) {
  if (mapTexture) {
    renderer->drawTexture(mapTexture, 0, 0, width, height);
  }
}
