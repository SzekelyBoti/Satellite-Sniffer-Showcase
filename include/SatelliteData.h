#pragma once
#include <string>

// Stores the basic TLE information of a satellite
struct SatelliteData {
public:
  std::string name;      // Satellite name
  std::string tleLine1;  // First line of the TLE data
  std::string tleLine2;  // Second line of the TLE data

public:
  // Constructor initializing name and TLE lines
  SatelliteData(const std::string &name,
                const std::string &line1,
                const std::string &line2);

  ~SatelliteData();      // Destructor (default behavior)
};
