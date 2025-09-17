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
    void updateAllPositions(TLEtoGPSConverter* converter);
    std::vector<GPSPosition> getPositions() const;

    std::vector<std::string> getSatelliteNames() const;
    void toggleSatellite(int index);
    bool isSatelliteVisible(int index) const;
    size_t getSatelliteCount() const;
};
