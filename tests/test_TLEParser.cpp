#include <gtest/gtest.h>
#include "TLEParser.h"

TEST(TLEParserTest, ParsesValidTLE) {
  std::string tle1 = "1 25544U 98067A   21075.59097222  .00002182  00000-0  43685-4 0  9990";
  std::string tle2 = "2 25544  51.6443 152.1593 0001775  87.7200  34.9747 15.48940037273145";

  TLEParser parser;
  auto result = parser.parse("ISS", tle1, tle2);
  EXPECT_EQ(result->name, "ISS");
}
