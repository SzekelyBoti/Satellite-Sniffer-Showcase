#pragma once
#include "Application.h"

#include <vector>

// Represents the different modes for updating the simulation
enum class UpdateMode {
    MANUAL,      // Updates only when manually triggered
    REALTIME,    // Updates in real time
    SIMULATION   // Updates according to a simulated time scale
};

class Application; // Forward declaration

// Manages simulation time, update speed, and mode of operation
class UpdateManager {
public:
    // Constructor: associates the manager with an application
    UpdateManager(Application* app);

    // Destructor
    ~UpdateManager();

    // Set the update mode (MANUAL, REALTIME, or SIMULATION)
    void setMode(UpdateMode newMode);

    // Set the speed multiplier for simulation updates
    void setSpeedMultiplier(double multiplier);

    // Increase simulation speed to the next predefined step
    void nextStep();

    // Decrease simulation speed to the previous predefined step
    void prevStep();

    // Advance the simulation time according to speed multiplier
    void tick();

    // Reset the simulation clock to zero
    void resetSimulation();

    // Get the current simulated time in seconds
    double getSimulatedTime() const;

    // Get the current speed multiplier
    double getSpeedMultiplier() const;

private:
    UpdateMode mode;           // Current update mode
    Application* application;  // Reference to the main application

    double simTime = 0.0;      // Simulated time in seconds
    double speedMultiplier = 1.0; // Current speed multiplier
    unsigned int lastTicks = 0;   // Last SDL_GetTicks reference
    std::vector<double> multipliers; // Predefined speed steps
    size_t currentIndex;           // Current index in multipliers
};


