#pragma once
#include <string>

#include "SatelliteData.h"

// Utility class for parsing TLE (Two-Line Element) data into SatelliteData objects.
class TLEParser {
public:
    TLEParser();
    ~TLEParser();

    // Parses the given TLE lines and returns a dynamically allocated SatelliteData object.
    // name: satellite name
    // line1, line2: TLE strings
    // Returns a pointer to a new SatelliteData instance (caller is responsible for deletion)
    SatelliteData* parse(const std::string& name,
                         const std::string& line1,
                         const std::string& line2);
};
