#include <iostream>
#include "include/SGP4Converter.h"
#include "include/GPSPosition.h"

void testSGP4Conversion() {
    SGP4Converter converter;

    // Test with ISS TLE data
    const std::string issLine1 = "1 25544U 98067A   24058.45833333  .00020694  00000-0  37528-3 0  9992";
    const std::string issLine2 = "2 25544  51.6415  55.8090 0003528  75.1119  35.6963 15.49957205426916";

    try {
        const GPSPosition issPosition = converter.convert(issLine1, issLine2);
        std::cout << "ISS Position:" << std::endl;
        std::cout << "Latitude: " << issPosition.latitude << "°" << std::endl;
        std::cout << "Longitude: " << issPosition.longitude << "°" << std::endl;
        std::cout << "Altitude: " << issPosition.altitude << " meters" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error converting ISS TLE: " << e.what() << std::endl;
    }

    // Test with Hubble TLE data
    const std::string hstLine1 = "1 20580U 90037B   24058.45833333  .00000786  00000-0  25265-4 0  9991";
    const std::string hstLine2 = "2 20580  28.4693 288.4052 0002897 321.7772  38.2478 15.09284128822022";

    try {
        const GPSPosition hstPosition = converter.convert(hstLine1, hstLine2);
        std::cout << "\nHubble Position:" << std::endl;
        std::cout << "Latitude: " << hstPosition.latitude << "°" << std::endl;
        std::cout << "Longitude: " << hstPosition.longitude << "°" << std::endl;
        std::cout << "Altitude: " << hstPosition.altitude << " meters" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error converting Hubble TLE: " << e.what() << std::endl;
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    testSGP4Conversion();
    return 0;
}