#pragma once
#include <string>

// Base class representing any asset that can be rendered (e.g., images, icons, maps)
class RenderableAsset {
public:
  RenderableAsset() = default;                      // Default constructor
  explicit RenderableAsset(const std::string& file); // Load asset from file
  virtual ~RenderableAsset() = default;            // Virtual destructor for safe inheritance

  // Loads the asset from the given filename
  virtual bool load(const std::string& filename);

  // Returns the file path of the loaded asset
  const std::string& getFile() const;

protected:
  std::string filePath; // Path to the asset file
};
