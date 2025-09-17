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
    /*
    // Setup SDL renderer
    SDLRenderer renderer;
    if (!renderer.create(2560, 1440, "Satellite Tracker")) return -1;

    // Load Earth map
    EarthMap earth("../src/earth.png");
    MapRenderer map(&renderer);

    if (!map.loadMap(earth)) {
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
    */

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