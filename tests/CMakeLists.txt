cmake_minimum_required(VERSION 3.20)

set(TEST_SOURCES
        test_main.cpp
        test_GPSPosition.cpp
        test_EarthMap.cpp
        test_SatelliteManager.cpp
        test_SGP4Converter.cpp
        test_TLEParser.cpp
        test_Satellite.cpp
        test_UpdateManager.cpp
)

add_executable(SatelliteTests ${TEST_SOURCES})
target_include_directories(SatelliteTests PRIVATE ../include)

target_link_libraries(SatelliteTests
        PRIVATE
        gtest
        gtest_main
        satellite_lib
)

add_test(NAME SatelliteTests COMMAND SatelliteTests)


