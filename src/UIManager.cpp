#include "UIManager.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>

/**
 * @brief Constructs a UIManager with a given SDL_Renderer and screen dimensions.
 *
 * Initializes UI-related state, including dropdown visibility, selected and
 * hovered satellites, and the simulation speed multiplier.
 *
 * @param renderer Pointer to the SDL_Renderer used for drawing UI elements.
 * @param width Width of the screen or UI area.
 * @param height Height of the screen or UI area.
 */
UIManager::UIManager(SDL_Renderer* renderer, int width, int height)
    : renderer(renderer), font(nullptr), width(width), height(height),
      showUI(true), dropdownOpen(false), selectedSatellite(-1), hoveredSatellite(-1), speedMultiplier(1.0) {}

UIManager::~UIManager() {
    if (font) {
        TTF_CloseFont(font);
    }
}

/**
 * @brief Initializes the UIManager, setting up SDL_ttf and loading a font.
 *
 * Attempts to initialize the SDL_ttf library. Then tries to load a default
 * font from a local path, and falls back to a system font if necessary.
 *
 * @return true if initialization succeeds and a font is loaded, false otherwise.
 */
bool UIManager::init() {
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont("../src/fonts/arial.ttf", 16);
    if (!font) {
        font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16);
        if (!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
            return false;
        }
    }

    return true;
}

/**
 * @brief Renders the UI elements on the screen.
 *
 * Checks if the UI should be visible and if a font is loaded.
 * If so, it renders the satellite selection dropdown and the current
 * simulation speed indicator.
 *
 * @param satelliteNames A list of satellite names to display in the dropdown.
 * @param visibilityStates A corresponding list of booleans indicating whether
 *        each satellite is currently visible.
 */
void UIManager::render(const std::vector<std::string>& satelliteNames,
                      const std::vector<bool>& visibilityStates) {
    if (!showUI || !font) return;

    renderDropdown(satelliteNames, visibilityStates);
    renderSpeedIndicator();
}

/**
 * @brief Renders the satellite selection dropdown UI.
 *
 * Draws a dropdown box in the top-right corner of the screen, showing
 * the number of satellites and their visibility status. Handles both
 * open and closed states with a visual arrow indicator. When open,
 * displays a scrollable list of satellites with color-coded visibility
 * squares and highlights hovered items.
 *
 * @param satelliteNames List of satellite names to display in the dropdown.
 * @param visibilityStates List of booleans indicating each satellite's visibility.
 */
void UIManager::renderDropdown(const std::vector<std::string>& satelliteNames,
                              const std::vector<bool>& visibilityStates) {
    const int dropdownWidth = 300;
    const int dropdownHeight = 30;
    const int maxVisibleItems = 10;
    const int itemHeight = 25;

    SDL_Rect dropdownRect = {width - dropdownWidth - 10, 10, dropdownWidth, dropdownHeight};
    SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
    SDL_RenderFillRect(renderer, &dropdownRect);
    SDL_SetRenderDrawColor(renderer, 100, 100, 120, 255);
    SDL_RenderDrawRect(renderer, &dropdownRect);

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    if (dropdownOpen) {
        for (int i = 0; i < 8; ++i) {
            SDL_RenderDrawLine(renderer,
                width - 20, 20 - i,
                width - 20 - i, 20 + i);
            SDL_RenderDrawLine(renderer,
                width - 20, 20 - i,
                width - 20 + i, 20 + i);
        }
    } else {
        for (int i = 0; i < 8; ++i) {
            SDL_RenderDrawLine(renderer,
                width - 20, 20 + i,
                width - 20 - i, 20 - i);
            SDL_RenderDrawLine(renderer,
                width - 20, 20 + i,
                width - 20 + i, 20 - i);
        }
    }

    renderText("Satellites (" + std::to_string(satelliteNames.size()) + ")",
               width - dropdownWidth - 5, 15, {255, 255, 255, 255});

    if (dropdownOpen && !satelliteNames.empty()) {
        int listHeight = std::min(static_cast<int>(satelliteNames.size()), maxVisibleItems) * itemHeight;
        SDL_Rect listRect = {width - dropdownWidth - 10, 40, dropdownWidth, listHeight};

        SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
        SDL_RenderFillRect(renderer, &listRect);
        SDL_SetRenderDrawColor(renderer, 80, 80, 100, 255);
        SDL_RenderDrawRect(renderer, &listRect);

        for (int i = 0; i < std::min(static_cast<int>(satelliteNames.size()), maxVisibleItems); ++i) {
            SDL_Rect itemRect = {width - dropdownWidth - 10, 40 + i * itemHeight, dropdownWidth, itemHeight};

            if (hoveredSatellite == i) {
                SDL_SetRenderDrawColor(renderer, 60, 60, 80, 255);
                SDL_RenderFillRect(renderer, &itemRect);
            }

            SDL_Rect visRect = {width - dropdownWidth - 5, 42 + i * itemHeight, 16, 16};
            if (visibilityStates[i]) {
                SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
            }
            SDL_RenderFillRect(renderer, &visRect);
            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
            SDL_RenderDrawRect(renderer, &visRect);

            SDL_Color textColor = visibilityStates[i] ?
                SDL_Color{255, 255, 255, 255} :
                SDL_Color{150, 150, 150, 255};
            renderText(satelliteNames[i], width - dropdownWidth + 15, 42 + i * itemHeight, textColor);
        }

        if (satelliteNames.size() > maxVisibleItems) {
            SDL_Rect scrollBg = {width - 15, 40, 5, listHeight};
            SDL_SetRenderDrawColor(renderer, 70, 70, 90, 255);
            SDL_RenderFillRect(renderer, &scrollBg);
        }
    }
}

/**
 * @brief Renders the simulation speed indicator on the screen.
 *
 * Displays a rectangular panel in the top-left corner showing the current
 * simulation speed as text (e.g., "Speed: 4x") and a horizontal bar
 * representing the speed magnitude. The bar color changes based on the speed:
 * - Green for low speeds
 * - Yellow for medium speeds
 * - Red for high speeds
 *
 * Uses logarithmic scaling to map speed values to the bar width, providing
 * better visual feedback across a wide range of multipliers.
 */
void UIManager::renderSpeedIndicator() {
    if (!font) return;

    const int indicatorWidth = 200;
    const int indicatorHeight = 30;
    const int indicatorX = 10;
    const int indicatorY = 10;

    SDL_Rect bgRect = {indicatorX, indicatorY, indicatorWidth, indicatorHeight};
    SDL_SetRenderDrawColor(renderer, 30, 30, 40, 200);
    SDL_RenderFillRect(renderer, &bgRect);
    SDL_SetRenderDrawColor(renderer, 100, 100, 120, 255);
    SDL_RenderDrawRect(renderer, &bgRect);

    std::ostringstream speedStream;
    speedStream << "Speed: " << std::fixed << std::setprecision(1) << speedMultiplier << "x";
    std::string speedText = speedStream.str();

    renderText(speedText, indicatorX + 10, indicatorY, {255, 255, 255, 255});

    const int barWidth = 150;
    const int barHeight = 8;
    const int barX = indicatorX + 10;
    const int barY = indicatorY + 22;

    SDL_Rect barBg = {barX, barY, barWidth, barHeight};
    SDL_SetRenderDrawColor(renderer, 50, 50, 60, 255);
    SDL_RenderFillRect(renderer, &barBg);

    double logSpeed = std::log(speedMultiplier) / std::log(128.0);
    int filledWidth = static_cast<int>(barWidth * logSpeed);
    filledWidth = std::max(0, std::min(filledWidth, barWidth));

    if (filledWidth > 0) {
        SDL_Rect barFill = {barX, barY, filledWidth, barHeight};

        if (speedMultiplier < 8.0) {
            SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
        } else if (speedMultiplier < 32.0) {
            SDL_SetRenderDrawColor(renderer, 200, 200, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
        }
        SDL_RenderFillRect(renderer, &barFill);
    }
}

/**
 * @brief Handles SDL input events for the UI, specifically the satellite dropdown.
 *
 * Processes mouse clicks and mouse motion events:
 * - Clicking the dropdown header toggles its open/closed state.
 * - Clicking on an item in the open dropdown selects that satellite.
 * - Moving the mouse over items highlights them.
 *
 * @param e The SDL_Event to handle.
 * @return true if the event affected the UI (e.g., dropdown toggled or satellite selected),
 *         false otherwise.
 */
bool UIManager::handleEvent(const SDL_Event& e) {
    if (!showUI) return false;

    const int dropdownWidth = 300;
    const int dropdownHeight = 30;
    const int maxVisibleItems = 10;
    const int itemHeight = 25;

    SDL_Rect dropdownRect = {width - dropdownWidth - 10, 10, dropdownWidth, dropdownHeight};

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;

        std::cout << "Mouse click at: " << x << ", " << y << std::endl;

        if (x >= dropdownRect.x && x <= dropdownRect.x + dropdownRect.w &&
            y >= dropdownRect.y && y <= dropdownRect.y + dropdownRect.h) {
            dropdownOpen = !dropdownOpen;
            std::cout << "Dropdown toggled: " << (dropdownOpen ? "open" : "closed") << std::endl;
            return true;
            }

        if (dropdownOpen && x >= dropdownRect.x && x <= dropdownRect.x + dropdownRect.w &&
            y >= 40 && y <= 40 + maxVisibleItems * itemHeight) {
            int itemIndex = (y - 40) / itemHeight;
            std::cout << "Clicked item index: " << itemIndex << std::endl;

            if (itemIndex >= 0 && itemIndex < maxVisibleItems) {
                selectedSatellite = itemIndex;
                std::cout << "Selected satellite: " << selectedSatellite << std::endl;
                return true;
            }
            }
    }
    else if (e.type == SDL_MOUSEMOTION) {
        int x = e.motion.x;
        int y = e.motion.y;

        if (dropdownOpen && x >= dropdownRect.x && x <= dropdownRect.x + dropdownRect.w &&
            y >= 40 && y <= 40 + maxVisibleItems * itemHeight) {
            hoveredSatellite = (y - 40) / itemHeight;
            } else {
                hoveredSatellite = -1;
            }
    }

    return false;
}

/**
 * @brief Returns the index of the currently selected satellite in the dropdown.
 *
 * If no satellite is selected, returns -1.
 *
 * @return Index of selected satellite, or -1 if none.
 */
int UIManager::getSelectedSatellite() const {
    return selectedSatellite;
}

/**
 * @brief Toggles the visibility of the UI overlay.
 *
 * When called, this function will switch the `showUI` flag:
 * - If the UI is currently visible, it will be hidden.
 * - If the UI is currently hidden, it will be shown.
 */
void UIManager::toggleUI() {
    showUI = !showUI;
}

/**
 * @brief Checks whether the UI overlay is currently visible.
 *
 * @return true if the UI is visible, false otherwise.
 */
bool UIManager::isUIVisible() const {
    return showUI;
}

/**
 * @brief Sets the current speed multiplier used by the simulation.
 *
 * This value affects how fast the simulated time progresses relative to real time.
 *
 * @param multiplier The new speed multiplier to apply (e.g., 1.0 for real time, 2.0 for 2x speed).
 */
void UIManager::setSpeedMultiplier(double multiplier) {
    speedMultiplier = multiplier;
}

/**
 * @brief Renders a string of text at a specified position on the screen.
 *
 * This function creates a texture from the given text and color, and then
 * draws it using the SDL renderer at coordinates (x, y). After rendering,
 * the temporary texture is destroyed to free resources.
 *
 * @param text The string to render.
 * @param x The X-coordinate for the top-left corner of the text.
 * @param y The Y-coordinate for the top-left corner of the text.
 * @param color The color to use for rendering the text (SDL_Color).
 */
void UIManager::renderText(const std::string& text, int x, int y, SDL_Color color) {
    SDL_Texture* texture = createTextTexture(text, color);
    if (!texture) return;

    int texW, texH;
    SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
    SDL_Rect dstRect = {x, y, texW, texH};
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}

/**
 * @brief Creates an SDL_Texture from a text string using the current font.
 *
 * This function uses SDL_ttf to render the given text onto a surface, then
 * converts that surface into an SDL_Texture suitable for rendering with
 * the SDL renderer. The caller is responsible for rendering and eventually
 * destroying the returned texture.
 *
 * @param text The string to convert into a texture.
 * @param color The color to render the text in (SDL_Color).
 * @return SDL_Texture* Pointer to the created texture, or nullptr if creation fails.
 */
SDL_Texture* UIManager::createTextTexture(const std::string& text, SDL_Color color) {
    if (!font) return nullptr;

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "TTF_RenderText failed: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}