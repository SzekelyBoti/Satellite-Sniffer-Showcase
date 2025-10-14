#include "SatelliteIcon.h"

/**
 * @brief Constructs a SatelliteIcon with the given image file.
 *
 * @param file The path to the image representing the satellite icon.
 *
 * Inherits from RenderableAsset, so the file is stored and later used
 * by renderers to display the satellite on the screen.
 */
SatelliteIcon::SatelliteIcon(const std::string& file)
    : RenderableAsset(file) {}
