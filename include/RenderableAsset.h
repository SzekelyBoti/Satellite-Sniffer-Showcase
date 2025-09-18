#pragma once
#include <string>

class RenderableAsset {
public:
  RenderableAsset() = default;
  explicit RenderableAsset(const std::string& file);
  virtual ~RenderableAsset() = default;

  virtual bool load(const std::string& filename);
  const std::string& getFile() const;

protected:
  std::string filePath;
};
