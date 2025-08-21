#pragma once
#include "SDLRenderer.h"
#include <string>

class MapRenderer {
public:
  MapRenderer(SDLRenderer* renderer) : renderer(renderer) {}
  bool loadMap(const std::string& filename);
  void render(int width, int height);

private:
  SDLRenderer* renderer;
  SDL_Texture* mapTexture = nullptr;
};

