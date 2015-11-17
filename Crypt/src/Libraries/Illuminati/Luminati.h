#pragma once

#include "LightMap.h"

class Luminati
{
public:
    static inline LightMap *createLightMap(int w, int h)
    {
        return new LightMap(Dimension {0,0,w,h});
    }
};