#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "GPSPosition.h"
#include "MapRenderer.h"
#include "SDLRenderer.h"
#include "SGP4Converter.h"
#include "SatelliteIcon.h"
#include "SatelliteManager.h"
#include "SatelliteRenderer.h"
#include "UpdateManager.h"

int main() {
    SDLRenderer renderer;
    if (!renderer.create(1920, 1080, "Satellite Tracker")) return -1;

    EarthMap earth("../src/earth.png");
    MapRenderer map(&renderer);
    if (!map.loadMap(earth)) {
        std::cerr << "Failed to load map\n";
        return -1;
    }

    SatelliteIcon satellite("../src/satellite.png");
    SatelliteRenderer satelliteRenderer(&renderer);
    if (!satelliteRenderer.loadSatellite(satellite)) {
        std::cerr << "Failed to load satellite icon\n";
        return -1;
    }

    SGP4Converter converter;
    SatelliteManager manager;
    manager.loadFromFile("../src/satellites.txt");

    bool running = true;
    SDL_Event e;
    UpdateManager updateManager(nullptr);

    // Main loop
    while (running) {
        // --- Handle events ---
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    updateManager.nextStep();
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                    updateManager.prevStep();
                }
            }
        }

        // --- Update ---
        updateManager.tick();
        double simTime = updateManager.getSimulatedTime();
        manager.updateAllPositions(&converter, simTime);

        // --- Render ---
        renderer.clear();
        map.render(1920, 1080);
        satelliteRenderer.render(manager.getPositions(), 1920, 1080);
        renderer.present();
    }

    return 0;
}


