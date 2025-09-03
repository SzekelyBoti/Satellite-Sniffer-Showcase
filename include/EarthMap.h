#pragma once
#include <string>

class EarthMap {
public:
    EarthMap() = default;
    explicit EarthMap(const std::string& filename);

    bool load(const std::string& filename);
    const std::string& getFile() const { return mapFile; }

    void setZoom(float z) { zoomLevel = z; }
    float getZoom() const { return zoomLevel; }

private:
    std::string mapFile;
    float zoomLevel = 1.0f;
};