#include "SatelliteRenderer.h"
#include "SatelliteIcon.h"
#include <iostream>

/**
 * @brief Constructs a SatelliteRenderer with a given rendering interface.
 *
 * @param renderer Pointer to an IRenderer instance used for drawing satellites.
 *
 * This constructor initializes the SatelliteRenderer by storing the
 * provided renderer, which will be used for rendering satellite icons
 * on the map.
 */
SatelliteRenderer::SatelliteRenderer(IRenderer* renderer)
    : renderer(renderer) {}

/**
 * @brief Loads a satellite icon texture for rendering.
 *
 * @param icon Reference to a SatelliteIcon containing the file path of the image.
 * @return true if the texture was successfully loaded, false otherwise.
 *
 * This function first checks if there is an existing satellite texture loaded.
 * If so, it destroys the previous texture to prevent memory leaks. Then, it loads
 * the new satellite icon texture using the renderer and stores it in satelliteTexture.
 * If loading fails, an error message is printed and the function returns false.
 */
bool SatelliteRenderer::loadSatellite(const SatelliteIcon& icon) {
  if (satelliteTexture) {
    renderer->destroyTexture(satelliteTexture);
    satelliteTexture = nullptr;
  }

  satelliteTexture = renderer->loadTexture(icon.getFile());
  if (!satelliteTexture) {
    std::cerr << "Failed to load map texture: " << icon.getFile() << "\n";
    return false;
  }
  return true;
}

/**
 * @brief Renders all satellites on the screen based on their GPS positions.
 *
 * @param positions A vector of GPSPosition objects representing each satellite's location.
 * @param width The width of the rendering area (screen or map).
 * @param height The height of the rendering area (screen or map).
 *
 * This function iterates through all satellites and converts their geographic
 * coordinates (latitude and longitude) to screen coordinates using a simple
 * equirectangular projection:
 *   - X position is calculated by mapping longitude (-180° to 180°) to the screen width.
 *   - Y position is calculated by mapping latitude (90° to -90°) to the screen height.
 *
 * If a satellite texture is loaded, it draws the texture at the calculated position
 * with a fixed size (100x100 pixels). No texture is drawn if satelliteTexture is null.
 */
void SatelliteRenderer::render(const std::vector<GPSPosition>& positions, int width, int height) {
  for (const auto& pos : positions) {
    int x = static_cast<int>((pos.getLongitude() + 180.0) / 360.0 * width);
    int y = static_cast<int>((90.0 - pos.getLatitude()) / 180.0 * height);
    if (satelliteTexture) {
      renderer->drawTexture(satelliteTexture, x, y, 100 , 100);
    }
  }
}