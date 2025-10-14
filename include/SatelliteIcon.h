#pragma once
#include "RenderableAsset.h"

// Represents an icon for a satellite, inherits from RenderableAsset
class SatelliteIcon : public RenderableAsset {
public:
    SatelliteIcon() = default;                 // Default constructor
    explicit SatelliteIcon(const std::string& file); // Construct from a file path
};
