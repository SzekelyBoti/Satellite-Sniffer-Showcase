#include "Satellite.h"
#include "TLEtoGPSConverter.h"
#include "SatelliteData.h"

Satellite::Satellite(const std::string &name,
                     const std::string &tleLine1,
                     const std::string &tleLine2,
                     GPSPosition position) : name(name), tleLine1(tleLine1), tleLine2(tleLine2), position(position), visible(true) {
}

Satellite::~Satellite() {
}

void Satellite::updatePosition(TLEtoGPSConverter* converter, double simTime) {
    if (converter) {
        position = converter->convert(tleLine1, tleLine2, simTime);
    }
}

GPSPosition Satellite::getPosition() const { return position; }

void Satellite::initFromData(SatelliteData *data) {
    if (data) {
        name = data -> name;
        tleLine1 = data -> tleLine1;
        tleLine2 = data -> tleLine2;
        position = GPSPosition();
        visible = true;
    }
}

bool Satellite::isVisible() const {
    return visible;
}

void Satellite::setIsVisible(bool visible) {
    this->visible = visible;
}

const std::string &Satellite::getName() const {
    return name;
}
