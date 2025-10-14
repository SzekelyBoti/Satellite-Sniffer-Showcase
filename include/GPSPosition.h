#pragma once

// Represents a geographic position using latitude, longitude, and altitude
class GPSPosition {
public:
  GPSPosition() = default;

  // Constructs a GPS position with specified latitude, longitude, and altitude
  GPSPosition(double lat, double lon, double alt);

  ~GPSPosition() = default;

  // Getters
  double getLatitude() const;   // Returns latitude in degrees
  double getLongitude() const;  // Returns longitude in degrees
  double getAltitude() const;   // Returns altitude in meters

  // Setters
  void setLatitude(double lat);   // Sets latitude
  void setLongitude(double lon);  // Sets longitude
  void setAltitude(double alt);   // Sets altitude

private:
  double latitude = 0.0;   // Latitude in degrees
  double longitude = 0.0;  // Longitude in degrees
  double altitude = 0.0;   // Altitude in meters
};