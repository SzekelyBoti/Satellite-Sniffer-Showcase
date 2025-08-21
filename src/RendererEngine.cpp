#include "RenderEngine.h"

RenderEngine::RenderEngine(IRenderer *renderer)
    : renderer(renderer), mapRenderer(nullptr), satelliteRenderer(nullptr) {
}

RenderEngine::~RenderEngine() {
}

void RenderEngine::renderFrame(EarthMap *map, const std::vector<Satellite *> &satellites) {
}
