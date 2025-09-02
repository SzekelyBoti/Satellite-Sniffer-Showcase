#pragma once

class GPSPosition {
private:
public:
    //for testing lat, long, alt will be public in production it should be private
    double latitude;
    double longitude;
    double altitude;

    GPSPosition(double lat, double lon, double alt);
    ~GPSPosition();
};