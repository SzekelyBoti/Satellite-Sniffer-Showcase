#pragma once
#include <string>
#include "GPSPosition.h"

// Abstract interface for converting TLE data to GPS coordinates.
class TLEtoGPSConverter {
public:
  virtual ~TLEtoGPSConverter() = default;

  // Converts a satellite's TLE lines to a GPSPosition at a given simulation time.
  // line1, line2: TLE data strings
  // simTime: simulation time in seconds
  // Returns the calculated GPSPosition
  virtual GPSPosition convert(const std::string& line1,
                              const std::string& line2,
                              double simTime) = 0;
};