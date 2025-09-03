#ifndef IRENDERER_H
#define IRENDERER_H

#include <string>

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual bool create(int width, int height, const std::string& title) = 0;
    virtual void clear() = 0;
    virtual void present() = 0;

    virtual void* loadTexture(const std::string& file) = 0;

    virtual void drawTexture(void* texture, int x, int y, int w, int h) = 0;

    virtual void destroyTexture(void* texture) = 0;

    virtual void drawPoint(int x, int y) = 0;

    virtual void resize(int width, int height) = 0;
};

#endif // IRENDERER_H
