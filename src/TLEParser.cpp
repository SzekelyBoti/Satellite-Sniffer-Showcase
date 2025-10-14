#include "TLEParser.h"
#include "SatelliteData.h"

TLEParser::TLEParser() {
}

TLEParser::~TLEParser() {
}

/**
 * @brief Parses TLE data and creates a SatelliteData object.
 *
 * This function takes the name of the satellite and its two-line element (TLE)
 * data, then constructs a new SatelliteData object. It does not perform
 * validation on the TLE lines; it simply wraps the provided data into a
 * SatelliteData instance.
 *
 * @param name The name of the satellite.
 * @param line1 The first line of the TLE data.
 * @param line2 The second line of the TLE data.
 * @return SatelliteData* Pointer to the newly created SatelliteData object.
 */
SatelliteData *TLEParser::parse(const std::string &name,
                                const std::string &line1,
                                const std::string &line2) {
    return new SatelliteData(name, line1, line2);
}
