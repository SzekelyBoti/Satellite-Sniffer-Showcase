#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "MapRenderer.h"
#include "SDLRenderer.h"
#include "SatelliteRenderer.h"
#include "GPSPosition.h"
#include <vector>

int main() {
  SDLRenderer renderer;
  if(!renderer.create(2560, 1440, "Earth Map Viewer")) return -1;

  MapRenderer map(&renderer);
  if(!map.loadMap("earth.png")) {
    std::cerr << "Failed to load map\n";
    return -1;
  }

  SatelliteRenderer satelliteRenderer(&renderer);

  std::vector<GPSPosition> satellites = {
    { 0.0, 0.0, 0.0 },
    { 45.0, 90.0, 0.0 },
    { -30.0, -60.0, 0.0 }
  };

  bool running = true;
  SDL_Event e;

  while(running) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) running = false;
    }

    renderer.clear();

    map.render(2560, 1440);

    satelliteRenderer.render(satellites,2560,1440);

    renderer.present();
  }

  return 0;
}


