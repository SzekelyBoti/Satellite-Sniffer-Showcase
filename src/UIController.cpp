#include "UIController.h"
#include "Application.h"

UIController::UIController(Application* app) : application(app) {}
UIController::~UIController() {}
void UIController::handleInput() {}
void UIController::onToggleMode() {}
void UIController::onStep() {}