#pragma once
#include "IRenderer.h"
#include "EarthMap.h"

class MapRenderer {
public:
    explicit MapRenderer(IRenderer* renderer);
    ~MapRenderer() = default;

    bool loadMap(const EarthMap& map);
    void render(int width, int height);

private:
    IRenderer* renderer = nullptr;
    void* mapTexture = nullptr;
};
