#pragma once
#include "SDLRenderer.h"
#include "MapRenderer.h"
#include "SatelliteRenderer.h"
#include "SatelliteManager.h"
#include "SGP4Converter.h"
#include "UpdateManager.h"
#include "UIManager.h"

// Main application class that manages initialization, running the simulation, and rendering
class Application {
public:
    Application();
    ~Application();

    // Initializes SDL, renderers, UI, and loads satellite/map resources
    bool init();

    // Main application loop: handles events, updates simulation, renders
    void run();

private:
    bool isRunning;             // Tracks whether the main loop is active
    int screenWidth;            // Current screen width
    int screenHeight;           // Current screen height

    SDLRenderer renderer;       // SDL-based renderer
    MapRenderer* map = nullptr; // Handles rendering the Earth map
    SatelliteRenderer* satelliteRenderer = nullptr; // Renders satellites on the map
    SatelliteManager manager;   // Manages satellite data and visibility
    SGP4Converter converter;    // Converts TLE to GPS positions
    UpdateManager* updateManager = nullptr; // Controls simulation speed and time
    UIManager* ui = nullptr;    // Handles the on-screen UI
};