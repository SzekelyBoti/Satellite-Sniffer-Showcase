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
#include "UpdateManager.h"

#include "UIManager.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
        std::cerr << "SDL_GetCurrentDisplayMode Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return -1;
    }

    int screenWidth = displayMode.w;
    int screenHeight = displayMode.h;
  
    SDLRenderer renderer;
    if (!renderer.create(screenWidth, screenHeight, "Satellite Tracker")) return -1;

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
    UpdateManager updateManager(nullptr);

    // Main loop
    while (running) {
        // --- Handle events ---
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) running = false;
            if (ui.handleEvent(e)) {
                int selected = ui.getSelectedSatellite();
                if (selected != -1 && selected < manager.getSatelliteCount()) {
                    manager.toggleSatellite(selected);
                    std::cout << "Toggled satellite: " << selected << std::endl;
                }
            }
          if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    updateManager.nextStep();
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                    updateManager.prevStep();

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

        // --- Update ---
        updateManager.tick();
        double simTime = updateManager.getSimulatedTime();
        manager.updateAllPositions(&converter, simTime);
                 // --- Render ---
        renderer.clear();
        map.render(1920, 1080);
        satelliteRenderer.render(manager.getPositions(), 1920, 1080);
        map.render(screenWidth, screenHeight);

        // Update all satellite positions
        manager.updateAllPositions(&converter);

        // Render them
        satelliteRenderer.render(manager.getPositions(), screenWidth, screenHeight);

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
