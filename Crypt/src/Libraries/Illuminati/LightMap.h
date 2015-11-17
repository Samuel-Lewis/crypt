#pragma once

#include "MapObject.h"

class LightMap
{
public:
    LightMap(Dimension _dim);
    ~LightMap();

    void setGlobalLighting(float l);
    void fillMapEmpty();

    float valueAt(int x, int y);

    void addLightSource(LightSource *l);
    void addBlockingSource(BlockingObject *b);

    void removeLightSource(LightSource *l);

    void calculate(int phase);

    Dimension dim;

private:
    float **map;
    MapObject ***objects;

    float globalLighting;
};