#include "SatelliteData.h"

SatelliteData::SatelliteData(const std::string &name,
                             const std::string &line1,
                             const std::string &line2)
    : name(name), tleLine1(line1), tleLine2(line2) {
}

SatelliteData::~SatelliteData() {
}
