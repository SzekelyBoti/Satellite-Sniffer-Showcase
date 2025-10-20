#include "GPSPosition.h"

/**
 * @brief Constructs a GPSPosition object with given coordinates.
 *
 * @param lat Latitude in degrees.
 * @param lon Longitude in degrees.
 * @param alt Altitude in meters.
 *
 * Initializes a GPSPosition with the specified latitude, longitude, and altitude.
 */
GPSPosition::GPSPosition(double lat, double lon, double alt) 
    : latitude(lat), longitude(lon), altitude(alt) {}

/**
 * @brief Returns the latitude of the GPS position.
 *
 * @return Latitude in degrees.
 */
double GPSPosition::getLatitude() const { return latitude; }

/**
 * @brief Returns the longitude of the GPS position.
 * @return Longitude in degrees.
 */
double GPSPosition::getLongitude() const { return longitude; }

/**
 * @brief Returns the altitude of the GPS position.
 * @return Altitude in meters.
 */
double GPSPosition::getAltitude() const { return altitude; }

/**
 * @brief Sets the latitude of the GPS position.
 * @param lat Latitude in degrees.
 */
void GPSPosition::setLatitude(double lat) { latitude = lat; }

/**
 * @brief Sets the longitude of the GPS position.
 * @param lon Longitude in degrees.
 */
void GPSPosition::setLongitude(double lon) { longitude = lon; }

/**
 * @brief Sets the altitude of the GPS position.
 * @param alt Altitude in meters.
 */
void GPSPosition::setAltitude(double alt) { altitude = alt; }