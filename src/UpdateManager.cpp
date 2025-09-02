#include "UpdateManager.h"
#include "Application.h"

UpdateManager::UpdateManager(Application* app) : mode(UpdateMode::MANUAL), application(app) {}
UpdateManager::~UpdateManager() {}
void UpdateManager::setMode(UpdateMode newMode) {}
void UpdateManager::tick() {}