#pragma once
#include "IRenderer.h"

class SDLRenderer: public IRenderer {
public:
    SDLRenderer();
    ~SDLRenderer() override;
    void drawTexture(void* texture) override;
    void drawPoint(int x, int y) override;
    void create(int width, int height) override;
    void resize(int width, int height) override;
    void clear() override;
    void present() override;
};