#pragma once
#include "TLEtoGPSConverter.h"

// Converts TLE (Two-Line Element) data into GPS positions using the SGP4 algorithm.
class SGP4Converter : public TLEtoGPSConverter {
public:
  SGP4Converter();
  ~SGP4Converter() override;

  // Converts TLE lines to a GPSPosition at a given simulation time.
  // line1, line2: TLE strings
  // simTime: simulation time in seconds
  // Returns a GPSPosition object containing latitude, longitude, and altitude.
  GPSPosition convert(const std::string& line1,
                      const std::string& line2,
                      double simTime) override;
};
