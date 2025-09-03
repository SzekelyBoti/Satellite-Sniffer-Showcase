#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "MapRenderer.h"
#include "SDLRenderer.h"
#include "SatelliteRenderer.h"
#include "GPSPosition.h"
#include "SGP4Converter.h"

int main() {
    // Setup SDL renderer
    SDLRenderer renderer;
    if (!renderer.create(2560, 1440, "Satellite Tracker")) return -1;

    // Load Earth map
    MapRenderer map(&renderer);
    if (!map.loadMap("earth.png")) {
        std::cerr << "Failed to load map\n";
        return -1;
    }

    SatelliteRenderer satelliteRenderer(&renderer);
    SGP4Converter converter;

    // Collect real positions from TLE
    std::vector<GPSPosition> satellites;
    try {
        satellites.push_back(converter.convert(
            "1 25544U 98067A   24058.45833333  .00020694  00000-0  37528-3 0  9992",
            "2 25544  51.6415  55.8090 0003528  75.1119  35.6963 15.49957205426916"
        )); // ISS

        satellites.push_back(converter.convert(
            "1 20580U 90037B   24058.45833333  .00000786  00000-0  25265-4 0  9991",
            "2 20580  28.4693 288.4052 0002897 321.7772  38.2478 15.09284128822022"
        )); // Hubble
    } catch (const std::exception& e) {
        std::cerr << "Error converting TLE: " << e.what() << std::endl;
    }

    // Main loop
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        renderer.clear();

        // Draw Earth map
        map.render(2560, 1440);

        // Draw satellites (if we have any positions)
        satelliteRenderer.render(satellites, 2560, 1440);

        renderer.present();
    }

    return 0;
}

