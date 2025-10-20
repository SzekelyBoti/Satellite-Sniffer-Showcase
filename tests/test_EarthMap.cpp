#include <gtest/gtest.h>
#include "EarthMap.h"

TEST(EarthMapTest, DefaultZoomIsOne) {
  EarthMap map;
  EXPECT_FLOAT_EQ(map.getZoom(), 1.0f);
}

TEST(EarthMapTest, SetZoomChangesValue) {
  EarthMap map;
  map.setZoom(2.5f);
  EXPECT_FLOAT_EQ(map.getZoom(), 2.5f);
}

