#pragma once
#include <string>
#include "GPSPosition.h"

class TLEtoGPSConverter {
public:
    virtual ~TLEtoGPSConverter() = default;

  virtual GPSPosition convert(const std::string& line1, const std::string& line2, double simTime) = 0;
};
