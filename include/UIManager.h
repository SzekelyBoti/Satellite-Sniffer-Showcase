#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

class UIManager {
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    int width, height;
    bool showUI;
    bool dropdownOpen;
    int selectedSatellite;
    int hoveredSatellite;
    double speedMultiplier;

public:
    UIManager(SDL_Renderer* renderer, int width, int height);
    ~UIManager();

    bool init();
    void render(const std::vector<std::string>& satelliteNames,
                const std::vector<bool>& visibilityStates);
    bool handleEvent(const SDL_Event& e);
    int getSelectedSatellite() const;
    void toggleUI();
    bool isUIVisible() const;
    void setSpeedMultiplier(double multiplier);

private:
    void renderText(const std::string& text, int x, int y, SDL_Color color);
    SDL_Texture* createTextTexture(const std::string& text, SDL_Color color);
    void renderDropdown(const std::vector<std::string>& satelliteNames,
                       const std::vector<bool>& visibilityStates);
    void renderSpeedIndicator();
};