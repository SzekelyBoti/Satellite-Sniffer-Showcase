#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "MapRenderer.h"
#include "SDLRenderer.h"
#include "SGP4Converter.h"
#include "SatelliteIcon.h"
#include "SatelliteManager.h"
#include "SatelliteRenderer.h"

#include "UIManager.h"

int main() {
    SDLRenderer renderer;
    if (!renderer.create(1920, 1080, "Satellite Tracker")) return -1;

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        return -1;
    }

    EarthMap earth("../src/earth.png");
    MapRenderer map(&renderer);
    if (!map.loadMap(earth)) {
        std::cerr << "Failed to load map\n";
        TTF_Quit();
        return -1;
    }

    SatelliteIcon satellite("../src/satellite.png");
    SatelliteRenderer satelliteRenderer(&renderer);
    if (!satelliteRenderer.loadSatellite(satellite)) {
        std::cerr << "Failed to load satellite icon\n";
        TTF_Quit();
        return -1;
    }

    SGP4Converter converter;
    SatelliteManager manager;
    manager.loadFromFile("../src/satellites.txt");

    UIManager ui(renderer.getSDLRenderer(), 1920, 1080);
    if (!ui.init()) {
        std::cerr << "Failed to initialize UI\n";
        TTF_Quit();
        return -1;
    }

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (ui.handleEvent(e)) {
                int selected = ui.getSelectedSatellite();
                if (selected != -1 && selected < manager.getSatelliteCount()) {
                    manager.toggleSatellite(selected);
                    std::cout << "Toggled satellite: " << selected << std::endl;
                }
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB) {
                ui.toggleUI();
                std::cout << "UI toggled: " << (ui.isUIVisible() ? "visible" : "hidden") << std::endl;
            }

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_v:
                        for (size_t i = 0; i < manager.getSatelliteCount(); ++i) {
                            manager.toggleSatellite(i);
                        }
                        std::cout << "Toggled all satellites" << std::endl;
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
            }
        }

        renderer.clear();
        map.render(1920, 1080);

        manager.updateAllPositions(&converter);

        satelliteRenderer.render(manager.getPositions(), 1920, 1080);

        std::vector<bool> visibilityStates;
        for (size_t i = 0; i < manager.getSatelliteCount(); ++i) {
            visibilityStates.push_back(manager.isSatelliteVisible(i));
        }

        ui.render(manager.getSatelliteNames(), visibilityStates);

        renderer.present();

        SDL_Delay(16); // ~60 FPS
    }

    TTF_Quit();
    return 0;
}