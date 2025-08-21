#include "SatelliteRenderer.h"
#include "SatelliteIcon.h"
#include "GPSPosition.h"

SatelliteRenderer::SatelliteRenderer() : satelliteIcon(nullptr) {}
SatelliteRenderer::~SatelliteRenderer() {}
void SatelliteRenderer::render(const std::vector<GPSPosition>& positions) {}