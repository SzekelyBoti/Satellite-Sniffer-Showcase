#pragma once
#include "TLEtoGPSConverter.h"

class PyEphemConverter: public TLEtoGPSConverter {
    PyEphemConverter();
    ~PyEphemConverter() override;
    GPSPosition convert(const std::string& line1, const std::string& line2) override;
};