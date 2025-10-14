#ifndef IRENDERER_H
#define IRENDERER_H

#include <string>

// Abstract interface for a rendering system
class IRenderer {
public:
    virtual ~IRenderer() = default;

    // Initializes the rendering context with the given width, height, and window title
    virtual bool create(int width, int height, const std::string& title) = 0;

    // Clears the current render target (e.g., screen) to a default color
    virtual void clear() = 0;

    // Presents the rendered content on the screen
    virtual void present() = 0;

    // Loads a texture from a file and returns an opaque handle
    virtual void* loadTexture(const std::string& file) = 0;

    // Draws a texture at the specified position and size
    virtual void drawTexture(void* texture, int x, int y, int w, int h) = 0;

    // Destroys a previously loaded texture
    virtual void destroyTexture(void* texture) = 0;

    // Draws a single point at the specified coordinates
    virtual void drawPoint(int x, int y) = 0;

    // Resizes the rendering viewport or window
    virtual void resize(int width, int height) = 0;
};

#endif // IRENDERER_H
