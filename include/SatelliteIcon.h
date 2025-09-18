#pragma once
#include "RenderableAsset.h"

class SatelliteIcon : public RenderableAsset {
public:
    SatelliteIcon() = default;
    explicit SatelliteIcon(const std::string& file);
};
