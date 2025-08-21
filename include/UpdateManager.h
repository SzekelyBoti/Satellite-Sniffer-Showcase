#pragma once
#include "Application.h"
#include "UpdateMode.h"

class UpdateManager {
private:
    UpdateMode mode;
    Application* application;

public:
    UpdateManager(Application* app);
    ~UpdateManager();
    void setMode(UpdateMode newMode);
    void tick();
};
