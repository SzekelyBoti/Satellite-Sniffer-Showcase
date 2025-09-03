#pragma once
#include <string>

class SatelliteData {
private:
    std::string name;
    std::string tleLine1;
    std::string tleLine2;

public:
    SatelliteData(const std::string &name,
                  const std::string &line1,
                  const std::string &line2);

    ~SatelliteData();
};
