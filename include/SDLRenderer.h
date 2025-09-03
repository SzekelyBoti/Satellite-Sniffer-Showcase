#pragma once
#include "IRenderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

class SDLRenderer : public IRenderer {
public:
    SDLRenderer() = default;
    ~SDLRenderer() override;

    bool create(int width, int height, const std::string& title) override;
    void clear() override;
    void present() override;

    void* loadTexture(const std::string& file) override;
    void drawTexture(void* texture, int x, int y, int w, int h) override;
    void destroyTexture(void* texture) override;
    void drawPoint(int x, int y) override;
    void resize(int width, int height) override;

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};