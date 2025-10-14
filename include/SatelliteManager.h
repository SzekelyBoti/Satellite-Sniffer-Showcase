#pragma once
#include <vector>
#include <string>

#include "Satellite.h"

// Manages a collection of satellites: loading, updating positions, and visibility
class SatelliteManager {
private:
    std::vector<Satellite> satellites; // All satellites being managed

public:
    SatelliteManager();   // Constructor
    ~SatelliteManager();  // Destructor

    // Loads satellites from a TLE file
    void loadFromFile(const std::string& file);

    // Updates the position of all satellites using a TLE to GPS converter
    // simTime: the current simulation time in seconds
    void updateAllPositions(TLEtoGPSConverter* converter, double simTime);

    // Returns positions of all visible satellites
    std::vector<GPSPosition> getPositions() const;

    // Returns the names of all satellites
    std::vector<std::string> getSatelliteNames() const;

    // Toggles the visibility of a satellite at the given index
    void toggleSatellite(int index);

    // Returns true if the satellite at the given index is visible
    bool isSatelliteVisible(int index) const;

    // Returns the total number of satellites
    size_t getSatelliteCount() const;
};
