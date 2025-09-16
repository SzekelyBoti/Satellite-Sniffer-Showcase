#include "SatelliteManager.h"
#include <fstream>
#include "Satellite.h"
#include "TLEtoGPSConverter.h"
#include "GPSPosition.h"
#include "TLEParser.h"

SatelliteManager::SatelliteManager() {}
SatelliteManager::~SatelliteManager() {}

void SatelliteManager::loadFromFile(const std::string& file) {
    std::ifstream in(file);
    if (!in.is_open()) return;

    std::string name, line1, line2;
    TLEParser parser;

    while (std::getline(in, name) &&
        std::getline(in, line1) &&
        std::getline(in, line2)) {

        SatelliteData* data = parser.parse(name, line1, line2);

        Satellite sat ("", "", "", GPSPosition());
        sat.initFromData(data);
        satellites.push_back(sat);

        delete data;
    }
}

void SatelliteManager::updateAllPositions(TLEtoGPSConverter* converter) {
    for (auto& sat : satellites) {
        sat.updatePosition(converter);
    }
}

std::vector<GPSPosition> SatelliteManager::getPositions() const {
    std::vector<GPSPosition> positions;
    for (const auto& sat : satellites) {
        positions.push_back(sat.getPosition());
    }
    return positions;
}