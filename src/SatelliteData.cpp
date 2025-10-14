#include "SatelliteData.h"

/**
 * @brief Constructs a SatelliteData object from TLE (Two-Line Element) data.
 *
 * @param name  The name of the satellite.
 * @param line1 The first line of the TLE data.
 * @param line2 The second line of the TLE data.
 *
 * Stores the TLE information and satellite name for later use in orbit
 * calculations and conversions to GPS positions.
 */
SatelliteData::SatelliteData(const std::string &name,
                             const std::string &line1,
                             const std::string &line2)
    : name(name), tleLine1(line1), tleLine2(line2) {
}

SatelliteData::~SatelliteData() {
}
