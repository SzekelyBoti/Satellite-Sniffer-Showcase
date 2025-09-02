#include "SGP4Converter.h"
#include "GPSPosition.h"
#include "sgp4/libsgp4/Tle.h"
#include "sgp4/libsgp4/SGP4.h"
#include "sgp4/libsgp4/CoordTopocentric.h"
#include "sgp4/libsgp4/CoordGeodetic.h"
#include "sgp4/libsgp4/Observer.h"
#include "sgp4/libsgp4/DateTime.h"
#include <stdexcept>
#include <iostream>

SGP4Converter::SGP4Converter() {}

SGP4Converter::~SGP4Converter() {}

GPSPosition SGP4Converter::convert(const std::string& line1,
                                  const std::string& line2) {
    try {
        libsgp4::Tle tle("Satellite", line1, line2);

        libsgp4::SGP4 sgp4(tle);

        libsgp4::DateTime currentTime = libsgp4::DateTime::Now(true);

        libsgp4::Eci eci = sgp4.FindPosition(currentTime);

        libsgp4::CoordGeodetic geo = eci.ToGeodetic();

        double latitude = geo.latitude * 180.0 / M_PI;
        double longitude = geo.longitude * 180.0 / M_PI;
        double altitude = geo.altitude * 1000.0;

        return GPSPosition(latitude, longitude, altitude);

    } catch (const std::exception& e) {
        std::cerr << "SGP4 conversion error: " << e.what() << std::endl;
        throw;
    }
}