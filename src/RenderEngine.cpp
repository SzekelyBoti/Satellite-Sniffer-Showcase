#include "RenderEngine.h"

#include <memory>
#include <vector>

RenderEngine::RenderEngine(std::unique_ptr<IRenderer> rend)
    : renderer(std::move(rend)),
      mapRenderer(renderer.get()),
      satelliteRenderer(renderer.get())
{
}

void RenderEngine::renderFrame(int width, int height, const std::vector<GPSPosition>& satellitePositions) {
  if (!renderer) return;

  renderer->clear();

  mapRenderer.render(width, height);

  satelliteRenderer.render(satellitePositions, width, height);

  renderer->present();
}

