#pragma once

class GPSPosition {
private:
    double latitude;
    double longitude;
    double altitude;

public:
    GPSPosition(double lat, double lon, double alt);
    ~GPSPosition();
};