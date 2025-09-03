#pragma once

class GPSPosition {
public:
    GPSPosition() = default;
    GPSPosition(double lat, double lon, double alt);
    ~GPSPosition();

    double getLatitude() const;
    double getLongitude() const;
    double getAltitude() const;

    void setLatitude(double lat);
    void setLongitude(double lon);
    void setAltitude(double alt);

  private:
    double latitude = 0.0;
    double longitude = 0.0;
    double altitude = 0.0;
};