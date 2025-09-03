#pragma once
#include <vector>

#include "GPSPosition.h"
#include "SatelliteIcon.h"

class SatelliteRenderer {
private:
    SatelliteIcon* satelliteIcon;

public:
    SatelliteRenderer();
    ~SatelliteRenderer();
    void render(const std::vector<GPSPosition>& positions);
};
