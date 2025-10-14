#include "MapRenderer.h"
#include <iostream>

/**
 * @brief Constructs a MapRenderer with the given renderer interface.
 *
 * @param renderer Pointer to an IRenderer instance used for drawing.
 *
 * Initializes the MapRenderer by storing a reference to the renderer, which
 * will be used later to render the map texture to the screen.
 */
MapRenderer::MapRenderer(IRenderer* renderer)
    : renderer(renderer) {}

/**
 * @brief Loads the map texture from an EarthMap object.
 *
 * @param map Reference to an EarthMap containing the map image file path.
 * @return true if the texture was loaded successfully, false otherwise.
 *
 * If a previous map texture exists, it is destroyed first. Then it attempts
 * to load the new texture from the file path provided by the EarthMap object.
 * If loading fails, an error message is printed.
 */
bool MapRenderer::loadMap(const EarthMap& map) {
  if (mapTexture) {
    renderer->destroyTexture(mapTexture);
    mapTexture = nullptr;
  }

  mapTexture = renderer->loadTexture(map.getFile());
  if (!mapTexture) {
    std::cerr << "Failed to load map texture: " << map.getFile() << "\n";
    return false;
  }
  return true;
}

/**
 * @brief Renders the map texture to cover the given width and height.
 *
 * @param width The width of the area to render the map on.
 * @param height The height of the area to render the map on.
 *
 * If a valid map texture exists, it is drawn starting at (0,0) and scaled
 * to fill the specified width and height.
 */
void MapRenderer::render(int width, int height) {
  if (mapTexture) {
    renderer->drawTexture(mapTexture, 0, 0, width, height);
  }
}
