#pragma once
#include "TLEtoGPSConverter.h"

class SGP4Converter : public TLEtoGPSConverter {
public:
  SGP4Converter();
  ~SGP4Converter() override;
  GPSPosition convert(const std::string& line1,
                      const std::string& line2,
                      double simTime) override;
};
