#include "Satellite.h"
#include "TLEtoGPSConverter.h"
#include "SatelliteData.h"

Satellite::Satellite(const std::string &name,
                     const std::string &tleLine1,
                     const std::string &tleLine2,
                     GPSPosition position) : name(name), tleLine1(tleLine1), tleLine2(tleLine2), position(position) {
}

Satellite::~Satellite() {
}

void Satellite::updatePosition(TLEtoGPSConverter *converter) {
    if (converter) {
        position = converter-> convert(tleLine1, tleLine2);
    }
}

GPSPosition Satellite::getPosition() const { return position; }

void Satellite::initFromData(SatelliteData *data) {
    if (data) {
        name = data -> name;
        tleLine1 = data -> tleLine1;
        tleLine2 = data -> tleLine2;
        position = GPSPosition();
    }
}
