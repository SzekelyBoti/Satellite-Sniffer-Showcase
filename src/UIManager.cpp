#include "UIManager.h"
#include <iostream>
#include <algorithm>

UIManager::UIManager(SDL_Renderer* renderer, int width, int height)
    : renderer(renderer), font(nullptr), width(width), height(height),
      showUI(true), dropdownOpen(false), selectedSatellite(-1), hoveredSatellite(-1) {}

UIManager::~UIManager() {
    if (font) {
        TTF_CloseFont(font);
    }
}

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

void UIManager::render(const std::vector<std::string>& satelliteNames,
                      const std::vector<bool>& visibilityStates) {
    if (!showUI || !font) return;

    renderDropdown(satelliteNames, visibilityStates);
}

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

        // Background
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
int UIManager::getSelectedSatellite() const {
    return selectedSatellite;
}

void UIManager::toggleUI() {
    showUI = !showUI;
}

bool UIManager::isUIVisible() const {
    return showUI;
}

void UIManager::renderText(const std::string& text, int x, int y, SDL_Color color) {
    SDL_Texture* texture = createTextTexture(text, color);
    if (!texture) return;

    int texW, texH;
    SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
    SDL_Rect dstRect = {x, y, texW, texH};
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}

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