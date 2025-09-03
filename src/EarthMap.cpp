#include "EarthMap.h"
#include <iostream>

EarthMap::EarthMap(const std::string& filename) {
  load(filename);
}

bool EarthMap::load(const std::string& filename) {
  if (filename.empty()) {
    std::cerr << "EarthMap::load - empty filename\n";
    return false;
  }
  mapFile = filename;
  return true;
}
