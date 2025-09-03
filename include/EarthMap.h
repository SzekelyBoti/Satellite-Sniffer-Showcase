#pragma once
#include <string>

class EarthMap {
private:
    std::string mapFile;
    float zoomLevel;

public:
    EarthMap();
    ~EarthMap();
    void load(const std::string& filename);
    float getZoom() const;
};