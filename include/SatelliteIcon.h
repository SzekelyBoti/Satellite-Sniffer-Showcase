#pragma once
#include <string>

class SatelliteIcon {
public:
    SatelliteIcon() = default;
    explicit SatelliteIcon(const std::string& filename);

    bool load(const std::string& filename);
    const std::string& getFile() const { return satellitePng; }
private:
    std::string satellitePng;
};