#pragma once
#include "EarthMap.h"

class MapRenderer {
    MapRenderer();
    ~MapRenderer();
    void render(EarthMap* map);
};