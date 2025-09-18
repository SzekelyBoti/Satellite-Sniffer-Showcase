#pragma once
#include "Application.h"

#include <vector>

enum class UpdateMode {
    MANUAL,
    REALTIME,
    SIMULATION
};

class UpdateManager {
public:
    UpdateManager(Application* app);
    ~UpdateManager();

    void setMode(UpdateMode newMode);
    void setSpeedMultiplier(double multiplier);
    void nextStep();
    void prevStep();

    void tick();                // advance simulated time
    void resetSimulation();     // reset simulation clock
    double getSimulatedTime() const;
    double getSpeedMultiplier() const;

private:
    UpdateMode mode;
    Application* application;

    double simTime = 0.0;       // simulated time in seconds
    double speedMultiplier = 1.0;
    unsigned int lastTicks = 0; // last SDL_GetTicks reference
    std::vector<double> multipliers;
    size_t currentIndex;
};


