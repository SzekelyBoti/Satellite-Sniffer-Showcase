#include "SatelliteManager.h"
#include "TLEtoGPSConverter.h"
#include "GPSPosition.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>

class MockConverter : public TLEtoGPSConverter {
public:
    GPSPosition convert(const std::string&, const std::string&, double) override {
        return GPSPosition(10.0, 20.0, 400.0);
    }
};

TEST(SatelliteManagerTest, LoadFromFileReadsSatellites) {
    const char* testFile = "test_tle.txt";

    std::ofstream file(testFile);
    ASSERT_TRUE(file.is_open());
    file << "TEST_SAT\n"
         << "1 00005U 58002B   20000.00000000  .00000000  00000-0  00000-0 0  0000\n"
         << "2 00005  97.0000 100.0000 0010000 000.0000 000.0000 14.00000000    00\n";
    file.close();

    SatelliteManager manager;
    manager.loadFromFile(testFile);

    EXPECT_GT(manager.getSatelliteCount(), 0);
    auto names = manager.getSatelliteNames();
    EXPECT_FALSE(names.empty());
    EXPECT_EQ(names[0], "TEST_SAT");

    std::remove(testFile);
}

TEST(SatelliteManagerTest, UpdateAllPositionsUsesConverter) {
    const char* testFile = "test_tle_update.txt";

    std::ofstream file(testFile);
    ASSERT_TRUE(file.is_open());
    file << "UPDATE_SAT\n"
         << "1 00006U 58002B   20000.00000000  .00000000  00000-0  00000-0 0  0001\n"
         << "2 00006  98.0000 101.0000 0010000 000.0000 000.0000 14.00000000    00\n";
    file.close();

    SatelliteManager manager;
    manager.loadFromFile(testFile);
    EXPECT_GT(manager.getSatelliteCount(), 0);

    MockConverter converter;
    manager.updateAllPositions(&converter, 1000.0);

    auto positions = manager.getPositions();
    EXPECT_FALSE(positions.empty());
    EXPECT_NEAR(positions[0].getLatitude(), 10.0, 1e-6);
    EXPECT_NEAR(positions[0].getLongitude(), 20.0, 1e-6);
    EXPECT_NEAR(positions[0].getAltitude(), 400.0, 1e-6);

    std::remove(testFile);
}


