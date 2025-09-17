#pragma once
#include <string>

#include "GPSPosition.h"
#include "SatelliteData.h"
#include "TLEtoGPSConverter.h"

class Satellite {
private:
    std::string name;
    std::string tleLine1;
    std::string tleLine2;
    GPSPosition position;
    bool visible;

public:
    Satellite(const std::string &name,
              const std::string &tleLine1,
              const std::string &tleLine2,
              GPSPosition position);

    ~Satellite();

    void updatePosition(TLEtoGPSConverter *converter);

    GPSPosition getPosition() const;

    void initFromData(SatelliteData *data);

    bool isVisible() const;
    void setIsVisible(bool visible);
    const std::string& getName() const;
};
