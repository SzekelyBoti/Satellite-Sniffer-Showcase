#pragma once
#include "SDLRenderer.h"
#include "MapRenderer.h"
#include "SatelliteRenderer.h"
#include "SatelliteManager.h"
#include "SGP4Converter.h"
#include "UpdateManager.h"
#include "UIManager.h"

class UpdateManager;

class Application {
public:
    Application();
    ~Application();

    bool init();
    void run();
    void cleanup();

private:
    bool isRunning;

    int screenWidth;
    int screenHeight;

    SDLRenderer renderer;
    MapRenderer* map = nullptr;
    SatelliteRenderer* satelliteRenderer = nullptr;
    SatelliteManager manager;
    SGP4Converter converter;
    UpdateManager* updateManager = nullptr;
    UIManager* ui = nullptr;
};