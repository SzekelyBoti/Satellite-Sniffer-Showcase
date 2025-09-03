#include "SDLRenderer.h"

SDLRenderer::~SDLRenderer() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

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

void SDLRenderer::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SDLRenderer::present() {
    SDL_RenderPresent(renderer);
}

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

void SDLRenderer::drawTexture(void* texture, int x, int y, int w, int h) {
    SDL_Texture* tex = static_cast<SDL_Texture*>(texture);
    SDL_Rect dst{ x, y, w, h };
    SDL_RenderCopy(renderer, tex, nullptr, &dst);
}

void SDLRenderer::destroyTexture(void* texture) {
    if (texture) {
        SDL_DestroyTexture(static_cast<SDL_Texture*>(texture));
    }
}

void SDLRenderer::drawPoint(int x, int y) {
    SDL_Rect rect { x - 2, y - 2, 5, 5 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void SDLRenderer::resize(int width, int height) {
    if (window) {
        SDL_SetWindowSize(window, width, height);
    }
}
