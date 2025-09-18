#include "Application.h"
#include "UpdateManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "EarthMap.h"
#include "SatelliteIcon.h"

Application::Application() : isRunning(false), screenWidth(0), screenHeight(0) {}
Application::~Application() {}

bool Application::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
        std::cerr << "SDL_GetCurrentDisplayMode Error: " << SDL_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    screenWidth = displayMode.w;
    screenHeight = displayMode.h;

    if (!renderer.create(screenWidth, screenHeight, "Satellite Tracker")) {
        return false;
    }

    // Load earth map
    EarthMap earth("../src/earth.png");
    map = new MapRenderer(&renderer);
    if (!map->loadMap(earth)) {
        std::cerr << "Failed to load map\n";
        return false;
    }

    // Load satellite icon
    SatelliteIcon satellite("../src/satellite.png");
    satelliteRenderer = new SatelliteRenderer(&renderer);
    if (!satelliteRenderer->loadSatellite(satellite)) {
        std::cerr << "Failed to load satellite icon\n";
        return false;
    }

    // Load TLEs
    manager.loadFromFile("../src/satellites.txt");

    // UI
    ui = new UIManager(renderer.getSDLRenderer(), screenWidth, screenHeight);
    if (!ui->init()) {
        std::cerr << "Failed to initialize UI\n";
        return false;
    }

    // Update manager
    updateManager = new UpdateManager(this);

    isRunning = true;
    return true;
}

void Application::run() {
    SDL_Event e;

    while (isRunning) {
        // --- Events ---
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
            else if (ui->handleEvent(e)) {
                int selected = ui->getSelectedSatellite();
                if (selected != -1 && selected < manager.getSatelliteCount()) {
                    manager.toggleSatellite(selected);
                }
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT: updateManager->nextStep(); break;
                    case SDLK_LEFT:  updateManager->prevStep(); break;
                    case SDLK_TAB:   ui->toggleUI(); break;
                    case SDLK_v:
                        for (size_t i = 0; i < manager.getSatelliteCount(); ++i)
                            manager.toggleSatellite(i);
                        break;
                    case SDLK_ESCAPE: isRunning = false; break;
                }
            }
        }

        // --- Update ---
        updateManager->tick();
        double simTime = updateManager->getSimulatedTime();
        manager.updateAllPositions(&converter, simTime);

        // --- Render ---
        renderer.clear();

        map->render(screenWidth, screenHeight);
        satelliteRenderer->render(manager.getPositions(), screenWidth, screenHeight);

        std::vector<bool> visibilityStates;
        for (size_t i = 0; i < manager.getSatelliteCount(); ++i)
            visibilityStates.push_back(manager.isSatelliteVisible(i));

        ui->render(manager.getSatelliteNames(), visibilityStates);

        renderer.present();

        SDL_Delay(16); // ~60 FPS
    }
}

void Application::cleanup() {
    delete map;
    delete satelliteRenderer;
    delete ui;
    delete updateManager;

    TTF_Quit();
    SDL_Quit();
}

