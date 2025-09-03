#include "SatelliteManager.h"
#include "Satellite.h"
#include "TLEtoGPSConverter.h"
#include "GPSPosition.h"

SatelliteManager::SatelliteManager() {}
SatelliteManager::~SatelliteManager() {}
void SatelliteManager::loadFromFile(const std::string& file) {}
void SatelliteManager::updateAllPositions(TLEtoGPSConverter* converter) {}
std::vector<GPSPosition> SatelliteManager::getPositions() const { return {}; }