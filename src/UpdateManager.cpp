#include "UpdateManager.h"
#include <SDL.h>
#include <iostream>
#include <ostream>
#include "Application.h"

UpdateManager::UpdateManager(Application* app)
    : mode(UpdateMode::MANUAL),
      application(app),
      simTime(0.0),
      speedMultiplier(1.0),
      currentIndex(0) {
  multipliers = {1.0,4.0,8.0,16.0,32.0,64.0,128.0};
}


UpdateManager::~UpdateManager() {}

void UpdateManager::setMode(UpdateMode newMode) {
  mode = newMode;
}

void UpdateManager::setSpeedMultiplier(double multiplier) {
  if (multiplier > 0.0) {
    speedMultiplier = multiplier;
  }
}

void UpdateManager::nextStep() {
  currentIndex = (currentIndex + 1) % multipliers.size();
  speedMultiplier = multipliers[currentIndex];
  std::cout << "Speed: " << speedMultiplier << std::endl;
}

void UpdateManager::prevStep() {
  if (currentIndex == 0) currentIndex = multipliers.size() - 1;
  else currentIndex--;
  speedMultiplier = multipliers[currentIndex];
  std::cout << "Speed: " << speedMultiplier << std::endl;
}



void UpdateManager::resetSimulation() {
  simTime = 0.0;
  lastTicks = SDL_GetTicks();
}

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

double UpdateManager::getSimulatedTime() const {
  return simTime;
}


double UpdateManager::getSpeedMultiplier() const {
  return speedMultiplier;
}