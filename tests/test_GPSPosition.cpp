#include <gtest/gtest.h>
#include "GPSPosition.h"

TEST(GPSPositionTest, DefaultConstructor) {
  GPSPosition pos;
  EXPECT_DOUBLE_EQ(pos.getLatitude(), 0.0);
  EXPECT_DOUBLE_EQ(pos.getLongitude(), 0.0);
  EXPECT_DOUBLE_EQ(pos.getAltitude(), 0.0);
}

TEST(GPSPositionTest, ParameterizedConstructor) {
  GPSPosition pos(12.34, 56.78, 910.11);
  EXPECT_DOUBLE_EQ(pos.getLatitude(), 12.34);
  EXPECT_DOUBLE_EQ(pos.getLongitude(), 56.78);
  EXPECT_DOUBLE_EQ(pos.getAltitude(), 910.11);
}

TEST(GPSPositionTest, SettersWorkCorrectly) {
  GPSPosition pos;
  pos.setLatitude(45.0);
  pos.setLongitude(-120.5);
  pos.setAltitude(1000.0);

  EXPECT_DOUBLE_EQ(pos.getLatitude(), 45.0);
  EXPECT_DOUBLE_EQ(pos.getLongitude(), -120.5);
  EXPECT_DOUBLE_EQ(pos.getAltitude(), 1000.0);
}
