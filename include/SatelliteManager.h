#pragma once
#include <vector>
#include <string>

#include "Satellite.h"

class SatelliteManager {
private:
    std::vector<Satellite> satellites;
public:
    SatelliteManager();
    ~SatelliteManager();
    void loadFromFile(const std::string& file);
    void updateAllPositions(TLEtoGPSConverter* converter, double simTime);
    std::vector<GPSPosition> getPositions() const;
};
