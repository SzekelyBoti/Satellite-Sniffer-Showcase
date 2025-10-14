#include "SGP4Converter.h"
#include "GPSPosition.h"
#include "sgp4/libsgp4/Tle.h"
#include "sgp4/libsgp4/SGP4.h"
#include "sgp4/libsgp4/CoordGeodetic.h"
#include "sgp4/libsgp4/DateTime.h"
#include <stdexcept>
#include <iostream>
#define USE_MATH_DEFINES
#include <cmath>

SGP4Converter::SGP4Converter() {}
SGP4Converter::~SGP4Converter() {}

/**
 * @brief Converts TLE data into a GPSPosition at a specified simulation time.
 *
 * This function uses the SGP4 algorithm to calculate the satellite's
 * Earth-centered position from the given two-line element (TLE) data. The
 * position is returned as latitude, longitude, and altitude. The simulation
 * time `simTime` is added to a fixed start time (the first time this function
 * is called) to compute the satellite's position at the desired moment.
 *
 * @param line1 The first line of the TLE data.
 * @param line2 The second line of the TLE data.
 * @param simTime Simulation time in seconds since the start of the simulation.
 * @return GPSPosition The satellite's position at the specified simulation time.
 * @throws std::exception if SGP4 computation fails.
 */
GPSPosition SGP4Converter::convert(const std::string& line1,
                                  const std::string& line2,
                                  double simTime) {
    try {
        libsgp4::Tle tle("Satellite", line1, line2);
        libsgp4::SGP4 sgp4(tle);

        static libsgp4::DateTime simStart = libsgp4::DateTime::Now(true);

        libsgp4::DateTime simTimePoint = simStart.AddSeconds(simTime);

        libsgp4::Eci eci = sgp4.FindPosition(simTimePoint);
        libsgp4::CoordGeodetic geo = eci.ToGeodetic();

        double latitude  = geo.latitude  * 180.0 / M_PI;
        double longitude = geo.longitude * 180.0 / M_PI;
        double altitude  = geo.altitude * 1000.0;

        return GPSPosition(latitude, longitude, altitude);

    } catch (const std::exception& e) {
        std::cerr << "SGP4 conversion error at time "
                  << simTime << "s: " << e.what() << std::endl;
        throw;
    }
}

