#pragma once
#include "IRenderer.h"
#include "EarthMap.h"

// Handles rendering of an Earth map texture onto the screen
class MapRenderer {
public:
    explicit MapRenderer(IRenderer* renderer);  // Constructor using an abstract renderer
    ~MapRenderer() = default;                   // Default destructor

    // Loads the map texture from an EarthMap object
    bool loadMap(const EarthMap& map);

    // Draws the loaded map to cover the given width and height
    void render(int width, int height);

private:
    IRenderer* renderer = nullptr;  // Pointer to the renderer used for drawing
    void* mapTexture = nullptr;     // Texture object for the map
};
