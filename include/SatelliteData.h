#pragma once
#include <string>

struct SatelliteData {
public:
    std::string name;
    std::string tleLine1;
    std::string tleLine2;

public:
    SatelliteData(const std::string &name,
                  const std::string &line1,
                  const std::string &line2);

    ~SatelliteData();
};
