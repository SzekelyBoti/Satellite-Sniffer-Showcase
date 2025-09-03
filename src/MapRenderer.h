#pragma once
#include <string>
#include "IRenderer.h"

class MapRenderer {
public:
  explicit MapRenderer(IRenderer* renderer);
  ~MapRenderer() = default;

  bool loadMap(const std::string& filename);
  void render(int width, int height);

private:
  IRenderer* renderer = nullptr;
  void* mapTexture = nullptr;
};




