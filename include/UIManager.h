#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

// UIManager handles rendering and interaction with the UI overlay.
// It displays satellite lists, selection dropdowns, and speed indicators.
class UIManager {
private:
    SDL_Renderer* renderer;    // SDL renderer used for drawing
    TTF_Font* font;            // Font used for UI text
    int width, height;         // Dimensions of the rendering area
    bool showUI;               // Whether the UI is currently visible
    bool dropdownOpen;         // Whether the satellite dropdown is open
    int selectedSatellite;     // Index of the currently selected satellite
    int hoveredSatellite;      // Index of the satellite currently hovered by mouse
    double speedMultiplier;    // Current simulation speed multiplier

public:
    // Constructor: initializes the UI manager with a renderer and screen dimensions
    UIManager(SDL_Renderer* renderer, int width, int height);
    ~UIManager();

    // Initializes TTF and loads fonts
    bool init();

    // Renders the UI overlay (dropdowns, speed indicator)
    void render(const std::vector<std::string>& satelliteNames,
                const std::vector<bool>& visibilityStates);

    // Handles SDL events (mouse clicks, keyboard input)
    // Returns true if the event was handled by the UI
    bool handleEvent(const SDL_Event& e);

    // Returns the currently selected satellite index
    int getSelectedSatellite() const;

    // Toggles UI visibility on/off
    void toggleUI();

    // Checks if the UI is currently visible
    bool isUIVisible() const;

    // Updates the displayed speed multiplier
    void setSpeedMultiplier(double multiplier);

private:
    // Renders text at a given position with a specific color
    void renderText(const std::string& text, int x, int y, SDL_Color color);

    // Creates an SDL_Texture from a string of text
    SDL_Texture* createTextTexture(const std::string& text, SDL_Color color);

    // Renders the satellite selection dropdown
    void renderDropdown(const std::vector<std::string>& satelliteNames,
                        const std::vector<bool>& visibilityStates);

    // Renders the simulation speed indicator
    void renderSpeedIndicator();
};