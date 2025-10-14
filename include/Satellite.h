#pragma once
#include <string>
#include "GPSPosition.h"
#include "SatelliteData.h"
#include "TLEtoGPSConverter.h"

// Represents a satellite with TLE data, position, and visibility state
class Satellite {
private:
  std::string name;       // Satellite name
  std::string tleLine1;   // First line of TLE
  std::string tleLine2;   // Second line of TLE
  GPSPosition position;   // Current GPS position
  bool visible;           // Whether the satellite is visible on the map

public:
  // Constructor initializing satellite with TLE data and initial position
  Satellite(const std::string &name,
            const std::string &tleLine1,
            const std::string &tleLine2,
            GPSPosition position);

  ~Satellite();           // Destructor

  // Updates the satellite's position using a TLE-to-GPS converter
  void updatePosition(TLEtoGPSConverter *converter, double simTime);

  // Returns current GPS position
  GPSPosition getPosition() const;

  // Initializes satellite from SatelliteData object
  void initFromData(SatelliteData *data);

  // Visibility getters and setters
  bool isVisible() const;
  void setIsVisible(bool visible);

  // Returns satellite name
  const std::string& getName() const;
};
