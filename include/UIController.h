#pragma once
#include "Application.h"

class UIController {
private:
    Application* application;

public:
    UIController(Application* app);
    ~UIController();
    void handleInput();
    void onToggleMode();
    void onStep();
};
