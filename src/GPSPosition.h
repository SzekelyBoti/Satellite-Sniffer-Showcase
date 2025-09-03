#pragma once

class GPSPosition {
public:
  GPSPosition() = default;
  GPSPosition(double lat, double lon, double alt)
      : latitude(lat), longitude(lon), altitude(alt) {}

  double getLatitude() const { return latitude; }
  double getLongitude() const { return longitude; }
  double getAltitude() const { return altitude; }

  void setLatitude(double lat) { latitude = lat; }
  void setLongitude(double lon) { longitude = lon; }
  void setAltitude(double alt) { altitude = alt; }

private:
  double latitude = 0.0;
  double longitude = 0.0;
  double altitude = 0.0;
};

