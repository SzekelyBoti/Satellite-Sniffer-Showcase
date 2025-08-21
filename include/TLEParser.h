#pragma once
#include <string>

#include "SatelliteData.h"

class TLEParser {
public:
    TLEParser();
    ~TLEParser();
    SatelliteData* parse(const std::string& name, const std::string& line1, const std::string& line2);
};
