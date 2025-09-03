#include "GPSPosition.h"

GPSPosition::GPSPosition(double lat, double lon, double alt) 
    : latitude(lat), longitude(lon), altitude(alt) {}
GPSPosition::~GPSPosition() {}

double GPSPosition::getLatitude() const { return latitude; }
double GPSPosition::getLongitude() const { return longitude; }
double GPSPosition::getAltitude() const { return altitude; }
void GPSPosition::setLatitude(double lat) { latitude = lat; }
void GPSPosition::setLongitude(double lon) { longitude = lon; }
void GPSPosition::setAltitude(double alt) { altitude = alt; }