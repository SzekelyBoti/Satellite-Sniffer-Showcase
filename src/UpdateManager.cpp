#include "UpdateManager.h"
#include <SDL.h>
#include <iostream>
#include <ostream>
#include "Application.h"

/**
 * @brief Constructs an UpdateManager instance responsible for controlling simulation timing and speed.
 *
 * This constructor initializes key simulation parameters:
 *  - Sets the update mode to MANUAL by default.
 *  - Stores a pointer to the main Application instance (used for communication if needed).
 *  - Initializes the simulation time to 0 seconds.
 *  - Sets the default simulation speed multiplier to 1x (real-time).
 *  - Loads a list of predefined speed multipliers (1x–128x) that can be cycled through at runtime.
 *
 * @param app Pointer to the main Application object that owns this UpdateManager.
 */
UpdateManager::UpdateManager(Application* app)
    : mode(UpdateMode::MANUAL),
      application(app),
      simTime(0.0),
      speedMultiplier(1.0),
      currentIndex(0) {
  multipliers = {1.0,4.0,8.0,16.0,32.0,64.0,128.0};
}


UpdateManager::~UpdateManager() {}

/**
 * @brief Sets the current update mode for the simulation.
 *
 * This function changes how the UpdateManager updates simulation time.
 * The mode can be, for example, MANUAL or AUTOMATIC, depending on how
 * the simulation is controlled.
 *
 * @param newMode The new update mode to apply.
 */
void UpdateManager::setMode(UpdateMode newMode) {
  mode = newMode;
}

/**
 * @brief Sets a custom speed multiplier for the simulation.
 *
 * This function adjusts how quickly the simulation time progresses.
 * For example, a multiplier of 2.0 makes the simulation run twice as fast,
 * while 0.5 would make it run at half speed.
 * Only positive values are accepted.
 *
 * @param multiplier The new simulation speed multiplier (must be > 0.0).
 */
void UpdateManager::setSpeedMultiplier(double multiplier) {
  if (multiplier > 0.0) {
    speedMultiplier = multiplier;
  }
}

/**
 * @brief Cycles to the next predefined simulation speed.
 *
 * This function increments the current index within the predefined list of
 * speed multipliers (e.g., 1x, 4x, 8x, 16x, etc.). When the end of the list
 * is reached, it wraps around to the first multiplier.
 *
 * The selected speed multiplier determines how quickly satellite positions
 * update relative to real time.
 *
 * Example:
 *  - Current speed = 4x → pressing the right arrow calls nextStep()
 *  - New speed = 8x
 *
 * Also prints the new speed multiplier to the console for debugging purposes.
 */
void UpdateManager::nextStep() {
  currentIndex = (currentIndex + 1) % multipliers.size();
  speedMultiplier = multipliers[currentIndex];
  std::cout << "Speed: " << speedMultiplier << std::endl;
}

/**
 * @brief Cycles to the previous predefined simulation speed.
 *
 * This function decrements the current index within the predefined list of
 * speed multipliers (e.g., 1x, 4x, 8x, 16x, etc.). If the current index is
 * at the beginning of the list, it wraps around to the last multiplier.
 *
 * The updated speed multiplier determines how quickly satellite positions
 * advance relative to real time.
 *
 * Example:
 *  - Current speed = 8x → pressing the left arrow calls prevStep()
 *  - New speed = 4x
 *
 * Also prints the new speed multiplier to the console for debugging purposes.
 */
void UpdateManager::prevStep() {
  if (currentIndex == 0) currentIndex = multipliers.size() - 1;
  else currentIndex--;
  speedMultiplier = multipliers[currentIndex];
  std::cout << "Speed: " << speedMultiplier << std::endl;
}

/**
 * @brief Resets the simulation time to the beginning.
 *
 * This function sets the internal simulated time (`simTime`) back to 0.0
 * and updates the reference tick (`lastTicks`) to the current SDL time.
 *
 * This ensures that when the simulation restarts, satellite positions
 * and other time-dependent calculations begin from the initial state.
 *
 * Typically called when the user wants to restart the simulation or
 * reset the satellite positions to their starting values.
 */
void UpdateManager::resetSimulation() {
  simTime = 0.0;
  lastTicks = SDL_GetTicks();
}

/**
 * @brief Updates the simulation time based on elapsed real time.
 *
 * This function calculates the time difference since the last tick,
 * multiplies it by the current speed multiplier, and adds it to the
 * internal simulation time (`simTime`).
 *
 * The `lastTicks` value is updated to the current SDL tick count so that
 * the next call correctly measures elapsed time.
 *
 * If `lastTicks` is zero (first call), it simply sets the baseline
 * without updating `simTime`.
 *
 * This is typically called once per frame to advance the simulation
 * according to real time and the chosen speed multiplier.
 */
void UpdateManager::tick() {
  Uint32 currentTicks = SDL_GetTicks();

  if (lastTicks == 0) {
    lastTicks = currentTicks;
    return;
  }

  double deltaSeconds = (currentTicks - lastTicks) / 1000.0;
  simTime += deltaSeconds * speedMultiplier;

  lastTicks = currentTicks;
}

/**
 * @brief Returns the current simulation time.
 *
 * The simulation time (`simTime`) is updated by the `tick()` function
 * according to real elapsed time and the speed multiplier.
 *
 * @return Current simulated time in seconds.
 */
double UpdateManager::getSimulatedTime() const {
  return simTime;
}

/**
 * @brief Returns the current speed multiplier for the simulation.
 *
 * The speed multiplier scales the simulation time, allowing satellites
 * or other objects to move faster or slower than real time.
 *
 * @return Current speed multiplier (e.g., 1x, 2x, 4x, etc.).
 */
double UpdateManager::getSpeedMultiplier() const {
  return speedMultiplier;
}