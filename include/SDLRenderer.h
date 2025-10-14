#pragma once
#include "IRenderer.h"
#include <SDL.h>
#include <string>
#include <iostream>

// Implementation of IRenderer using SDL2 for graphics rendering.
class SDLRenderer : public IRenderer {
public:
    SDLRenderer() = default;
    ~SDLRenderer() override; // Cleans up SDL resources

    // Initializes SDL, creates a window and renderer.
    // width, height: window dimensions
    // title: window title
    // Returns true on success
    bool create(int width, int height, const std::string& title) override;

    // Clears the current render target (usually the screen)
    void clear() override;

    // Presents the current rendered content to the screen
    void present() override;

    // Loads an image file into a texture
    // Returns pointer to texture (void*) or nullptr on failure
    void* loadTexture(const std::string& file) override;

    // Draws a texture at the given position and size
    void drawTexture(void* texture, int x, int y, int w, int h) override;

    // Frees a previously loaded texture
    void destroyTexture(void* texture) override;

    // Draws a single point (as a small square) at given coordinates
    void drawPoint(int x, int y) override;

    // Resizes the window
    void resize(int width, int height) override;

    // Returns the raw SDL_Renderer pointer
    SDL_Renderer* getSDLRenderer();

private:
    SDL_Window* window = nullptr;     // SDL window handle
    SDL_Renderer* renderer = nullptr; // SDL renderer handle
};