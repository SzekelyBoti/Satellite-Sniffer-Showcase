#pragma once
#include <SDL.h>
#include <string>

class SDLRenderer {
public:
  SDLRenderer() = default;
  ~SDLRenderer();

  bool create(int width, int height, const std::string& title);
  void clear();
  void present();
  SDL_Texture* loadTexture(const std::string& file);
  void drawTexture(SDL_Texture* texture, int x, int y, int w, int h);

private:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
};

