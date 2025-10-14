#include "SDLRenderer.h"
#include <SDL_image.h>

/**
 * @brief Destructor for SDLRenderer.
 *
 * Cleans up SDL resources by destroying the SDL_Renderer and SDL_Window
 * if they were created. Finally, it calls SDL_Quit() to shut down all
 * initialized SDL subsystems.
 */
SDLRenderer::~SDLRenderer() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * @brief Initializes the SDL window and renderer.
 *
 * This function performs the following steps:
 * 1. Initializes the SDL video subsystem.
 * 2. Creates an SDL_Window with the given width, height, and title.
 * 3. Creates an accelerated SDL_Renderer for the window.
 * 4. Initializes SDL_image for PNG support.
 *
 * @param width Width of the window in pixels.
 * @param height Height of the window in pixels.
 * @param title Title of the window.
 * @return true if initialization was successful, false otherwise.
 */
bool SDLRenderer::create(int width, int height, const std::string& title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! " << SDL_GetError() << "\n";
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! " << IMG_GetError() << "\n";
        return false;
    }

    return true;
}

/**
 * @brief Clears the current rendering target with a black color.
 *
 * This prepares the renderer for drawing a new frame by filling it
 * entirely with black (RGBA: 0, 0, 0, 255). Should be called at the
 * start of each frame before rendering any objects.
 */
void SDLRenderer::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

/**
 * @brief Updates the screen with the rendered content.
 *
 * This function swaps the back buffer to the front, displaying
 * everything that has been drawn since the last call to clear().
 * Should be called at the end of each frame after all rendering
 * commands.
 */
void SDLRenderer::present() {
    SDL_RenderPresent(renderer);
}

/**
 * @brief Loads an image from a file and converts it to an SDL_Texture.
 *
 * @param file The file path to the image (supports PNG, JPG, etc.).
 * @return A pointer to the created SDL_Texture, or nullptr if loading fails.
 *
 * This function first loads the image into an SDL_Surface using SDL_image's
 * IMG_Load, then creates a hardware-accelerated texture from it. The surface
 * is freed after the texture is created. The returned texture can be used
 * for rendering with SDL_RenderCopy.
 */
void* SDLRenderer::loadTexture(const std::string& file) {
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface) {
        std::cerr << "Failed to load image " << file << "! " << IMG_GetError() << "\n";
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

/**
 * @brief Draws a given texture at a specified position and size.
 *
 * @param texture Pointer to the SDL_Texture to render.
 * @param x The x-coordinate of the top-left corner where the texture will be drawn.
 * @param y The y-coordinate of the top-left corner where the texture will be drawn.
 * @param w The width to draw the texture.
 * @param h The height to draw the texture.
 *
 * This function casts the generic void* pointer to SDL_Texture*, creates
 * a destination rectangle with the given position and size, and renders
 * the texture onto the current rendering target using SDL_RenderCopy.
 */
void SDLRenderer::drawTexture(void* texture, int x, int y, int w, int h) {
    SDL_Texture* tex = static_cast<SDL_Texture*>(texture);
    SDL_Rect dst{ x, y, w, h };
    SDL_RenderCopy(renderer, tex, nullptr, &dst);
}

/**
 * @brief Destroys a previously loaded SDL texture.
 *
 * @param texture Pointer to the SDL_Texture to be destroyed.
 *
 * This function safely casts the generic void* pointer to SDL_Texture*
 * and calls SDL_DestroyTexture to free the GPU resources associated with it.
 * Passing a nullptr has no effect.
 */
void SDLRenderer::destroyTexture(void* texture) {
    if (texture) {
        SDL_DestroyTexture(static_cast<SDL_Texture*>(texture));
    }
}

/**
 * @brief Draws a small red square representing a point at the specified coordinates.
 *
 * @param x The x-coordinate of the point's center.
 * @param y The y-coordinate of the point's center.
 *
 * This function draws a 5x5 red square centered at (x, y) on the current renderer.
 * It is used to visualize points such as satellite positions on the screen.
 */
void SDLRenderer::drawPoint(int x, int y) {
    SDL_Rect rect { x - 2, y - 2, 5, 5 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

/**
 * @brief Resizes the SDL window to the specified width and height.
 *
 * @param width  The new width of the window in pixels.
 * @param height The new height of the window in pixels.
 *
 * If the window exists, this function updates its size to the given dimensions.
 * The renderer automatically adapts to the new window size.
 */
void SDLRenderer::resize(int width, int height) {
    if (window) {
        SDL_SetWindowSize(window, width, height);
    }
}

/**
 * @brief Returns the underlying SDL_Renderer pointer.
 *
 * @return SDL_Renderer* Pointer to the SDL renderer used internally.
 *
 * This allows access to the raw SDL_Renderer for advanced operations
 * not directly exposed by SDLRenderer's wrapper functions.
 */
SDL_Renderer* SDLRenderer::getSDLRenderer() {
    return renderer;
}
