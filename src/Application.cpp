#include "Application.h"
#include "UpdateManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "EarthMap.h"
#include "SatelliteIcon.h"

/**
 * @brief Constructs the Application object with default values.
 * Initializes the application as not running and screen dimensions to 0.
 */
Application::Application() : isRunning(false), screenWidth(0), screenHeight(0) {}

Application::~Application() {
    delete map;
    delete satelliteRenderer;
    delete ui;
    delete updateManager;

    TTF_Quit();
    SDL_Quit();
}

/**
 * @brief Initializes the application, including SDL, TTF, display, rendering, map, satellites, UI, and update manager.
 *
 * @return true if initialization succeeded, false otherwise.
 *
 * Steps performed:
 * 1. Initialize SDL video subsystem.
 * 2. Initialize SDL_ttf for font rendering.
 * 3. Retrieve current display mode to set screen dimensions.
 * 4. Create the main renderer with full screen width and height.
 * 5. Load the Earth map texture via MapRenderer.
 * 6. Load the satellite icon via SatelliteRenderer.
 * 7. Load satellite data from a file into SatelliteManager.
 * 8. Initialize the UIManager for rendering UI elements.
 * 9. Create UpdateManager for simulation time management.
 * 10. Set application running flag to true if all steps succeed.
 */
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


    EarthMap earth("../src/resources/earth.png");
    map = new MapRenderer(&renderer);
    if (!map->loadMap(earth)) {
        std::cerr << "Failed to load map\n";
        return false;
    }


    SatelliteIcon satellite("../src/resources/satellite.png");
    satelliteRenderer = new SatelliteRenderer(&renderer);
    if (!satelliteRenderer->loadSatellite(satellite)) {
        std::cerr << "Failed to load satellite icon\n";
        return false;
    }


    manager.loadFromFile("../src/resources/satellites.txt");

    ui = new UIManager(renderer.getSDLRenderer(), screenWidth, screenHeight);
    if (!ui->init()) {
        std::cerr << "Failed to initialize UI\n";
        return false;
    }

    updateManager = new UpdateManager(this);

    isRunning = true;
    return true;
}

/**
 * @brief Main application loop. Handles events, updates simulation, and renders graphics.
 *
 * The loop runs while the application is active (`isRunning`):
 * 1. Event Handling:
 *    - Poll SDL events.
 *    - Quit event sets `isRunning` to false.
 *    - Delegate input events to UIManager.
 *    - Toggle satellite visibility if a satellite is selected from UI.
 *    - Handle keyboard shortcuts:
 *        - Right arrow: advance simulation speed step.
 *        - Left arrow: reverse simulation speed step.
 *        - Tab: toggle UI visibility.
 *        - 'v': toggle visibility for all satellites.
 *        - Escape: exit the application.
 *
 * 2. Update:
 *    - Update simulation time via UpdateManager.
 *    - Update satellite positions based on simulated time.
 *
 * 3. Render:
 *    - Clear the renderer.
 *    - Render Earth map.
 *    - Render satellites at their current positions.
 *    - Collect visibility states of satellites.
 *    - Update UI speed display.
 *    - Render UI (dropdown and speed indicator).
 *    - Present the final rendered frame.
 */
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
            visibilityStates.push_back(manager.isSatelliteVisible(static_cast<int>(i)));

        ui->setSpeedMultiplier(updateManager->getSpeedMultiplier());
        ui->render(manager.getSatelliteNames(), visibilityStates);

        renderer.present();

    }
}
