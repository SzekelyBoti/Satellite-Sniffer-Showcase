#pragma once
#include "TLEtoGPSConverter.h"
#include <string>

class SGP4Converter : public TLEtoGPSConverter {
public:
    SGP4Converter();
    ~SGP4Converter();
    GPSPosition convert(const std::string& line1, 
                       const std::string& line2) override;
};