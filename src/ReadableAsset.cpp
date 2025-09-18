#include "RenderableAsset.h"
#include <iostream>

RenderableAsset::RenderableAsset(const std::string& file) {
  load(file);
}

bool RenderableAsset::load(const std::string& filename) {
  if (filename.empty()) {
    std::cerr << "RenderableAsset::load - empty filename\n";
    return false;
  }
  filePath = filename;
  return true;
}

const std::string& RenderableAsset::getFile() const {
  return filePath;
}
