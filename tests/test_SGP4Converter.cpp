#include "SGP4Converter.h"
#include "TLEParser.h"
#include "TleException.h"
#include <gtest/gtest.h>

#include <cmath>

TEST(SGP4ConverterTest, ConvertsValidTLEToGPS) {
  SGP4Converter converter;
  TLEParser parser;

  std::string name = "ISS (ZARYA)";
  std::string line1 = "1 25544U 98067A   24300.54880787  .00010420  00000+0  19161-3 0  9991";
  std::string line2 = "2 25544  51.6426 307.3317 0003942  53.2088  56.8765 15.50452900446493";

  SatelliteData* data = parser.parse(name, line1, line2);

  GPSPosition pos = converter.convert(data->tleLine1, data->tleLine2, 0.0);
  
  EXPECT_GE(pos.getLatitude(), -90.0);
  EXPECT_LE(pos.getLatitude(), 90.0);
  EXPECT_GE(pos.getLongitude(), -180.0);
  EXPECT_LE(pos.getLongitude(), 180.0);
  EXPECT_TRUE(std::isfinite(pos.getAltitude()));

  delete data;
}

TEST(SGP4ConverterTest, HandlesInvalidTLEGracefully) {
  SGP4Converter converter;
  TLEParser parser;

  std::string name = "BROKEN";
  std::string line1 = "INVALID";
  std::string line2 = "ALSO BAD";

  SatelliteData* data = parser.parse(name, line1, line2);
  ASSERT_NE(data, nullptr);

  EXPECT_THROW({
        GPSPosition pos = converter.convert(data->tleLine1, data->tleLine2, 0.0);
    }, libsgp4::TleException);

  delete data;
}

TEST(SGP4ConverterTest, PositionChangesOverTime) {
  SGP4Converter converter;
  TLEParser parser;

  std::string name = "ISS (ZARYA)";
  std::string line1 = "1 25544U 98067A   24300.54880787  .00010420  00000+0  19161-3 0  9991";
  std::string line2 = "2 25544  51.6426 307.3317 0003942  53.2088  56.8765 15.50452900446493";

  SatelliteData* data = parser.parse(name, line1, line2);

  GPSPosition pos1 = converter.convert(data->tleLine1, data->tleLine2, 0.0);
  GPSPosition pos2 = converter.convert(data->tleLine1, data->tleLine2, 600);

  EXPECT_NE(pos1.getLatitude(), pos2.getLatitude());
  EXPECT_NE(pos1.getLongitude(), pos2.getLongitude());

  delete data;
}


