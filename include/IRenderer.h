#pragma once

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void drawTexture(void* texture) = 0;
    virtual void drawPoint(int x, int y) = 0;
    virtual void create(int width, int height) = 0;
    virtual void resize(int width, int height) = 0;
    virtual void clear() = 0;
    virtual void present() = 0;
};