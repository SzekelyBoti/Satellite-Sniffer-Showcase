#include "MapRenderer.h"

bool MapRenderer::loadMap(const std::string& filename) {
  mapTexture = renderer->loadTexture(filename);
  return mapTexture != nullptr;
}

void MapRenderer::render(int width, int height) {
  if(mapTexture) {
    renderer->drawTexture(mapTexture, 0, 0, width, height);
  }
}

