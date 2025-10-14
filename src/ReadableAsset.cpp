#include "RenderableAsset.h"
#include <iostream>

/**
 * @brief Constructs a RenderableAsset and loads the texture from a file.
 *
 * @param file Path to the image file to load as the asset's texture.
 *
 * This constructor automatically calls the `load` function to initialize
 * the asset with the given image file, making it ready for rendering.
 */
RenderableAsset::RenderableAsset(const std::string& file) {
  load(file);
}

/**
 * @brief Loads the asset from a given file path.
 *
 * @param filename Path to the image file.
 * @return true if the filename is valid and stored, false if the filename is empty.
 *
 * This function sets the internal filePath of the asset. It does not actually
 * load the image into memory; it only validates and stores the filename for later use.
 */
bool RenderableAsset::load(const std::string& filename) {
  if (filename.empty()) {
    std::cerr << "RenderableAsset::load - empty filename\n";
    return false;
  }
  filePath = filename;
  return true;
}

/**
 * @brief Retrieves the stored file path of the asset.
 *
 * @return Const reference to the file path string.
 *
 * This function allows access to the file path that was set when the asset
 * was loaded. It does not perform any file I/O; it simply returns the
 * stored path.
 */
const std::string& RenderableAsset::getFile() const {
  return filePath;
}
