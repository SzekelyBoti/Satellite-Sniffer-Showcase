#include "TLEParser.h"
#include "SatelliteData.h"

TLEParser::TLEParser() {
}

TLEParser::~TLEParser() {
}

SatelliteData *TLEParser::parse(const std::string &name,
                                const std::string &line1,
                                const std::string &line2) {
    return new SatelliteData(name, line1, line2);
}
