#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

#include "MapRenderer.h"
#include "SDLRenderer.h"
#include <iostream>

int main() {
  SDLRenderer renderer;
  if(!renderer.create(1024, 512, "Earth Map Viewer")) return -1;

  MapRenderer map(&renderer);
  if(!map.loadMap("earth.png")) {
    std::cerr << "Failed to load map\n";
    return -1;
  }

  bool running = true;
  SDL_Event e;

  while(running) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) running = false;
    }

    renderer.clear();
    map.render(1024, 512);
    renderer.present();
  }

  return 0;
}

