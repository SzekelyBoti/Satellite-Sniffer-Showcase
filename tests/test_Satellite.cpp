#include <gtest/gtest.h>
#include "Satellite.h"
#include "GPSPosition.h"
#include "SatelliteData.h"
#include "TLEtoGPSConverter.h"

// Mock converter that always returns a fixed GPSPosition
class MockConverter : public TLEtoGPSConverter {
public:
  GPSPosition convert(const std::string& line1,
                      const std::string& line2,
                      double simTime) override {
    return GPSPosition(10.0, 20.0, 400.0);
  }
};

TEST(SatelliteTest, InitFromDataSetsName) {
  SatelliteData data("TestSat", "line1...", "line2...");
  Satellite sat("", "", "", GPSPosition());
  sat.initFromData(&data);

  EXPECT_EQ(sat.getName(), "TestSat");
}

TEST(SatelliteTest, UpdatePositionUsesConverter) {
  SatelliteData data("TestSat", "line1...", "line2...");
  Satellite sat("", "", "", GPSPosition());
  sat.initFromData(&data);

  MockConverter converter;
  sat.updatePosition(&converter, 0.0);

  GPSPosition pos = sat.getPosition();
  EXPECT_DOUBLE_EQ(pos.getLatitude(), 10.0);
  EXPECT_DOUBLE_EQ(pos.getLongitude(), 20.0);
  EXPECT_DOUBLE_EQ(pos.getAltitude(), 400.0);
}

TEST(SatelliteTest, Visibility) {
  Satellite sat("Sat1", "", "", GPSPosition());
  EXPECT_TRUE(sat.isVisible());

  sat.setIsVisible(true);
  EXPECT_TRUE(sat.isVisible());

  sat.setIsVisible(false);
  EXPECT_FALSE(sat.isVisible());
}



