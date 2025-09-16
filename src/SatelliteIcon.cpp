#include "SatelliteIcon.h"
#include <iostream>

SatelliteIcon::SatelliteIcon(const std::string& filename) {
  load(filename);
}

bool SatelliteIcon::load(const std::string& filename) {
  if (filename.empty()) {
    std::cerr << "Satellite::load - empty filename\n";
    return false;
  }
  satellitePng = filename;
  return true;
}