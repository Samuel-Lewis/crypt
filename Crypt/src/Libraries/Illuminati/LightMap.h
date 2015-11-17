#pragma once

#include "MapObject.h"

class LightMap
{
public:
    LightMap(Dimension _dim);
    ~LightMap();

    void setGlobalLighting(float l);
    void fillMapEmpty();

    void addLightSource(LightSource *l);
    void addBlockingSource(BlockingObject *b);

    void calculate(int phase);

    Dimension dim;

private:
    float **map;
    MapObject ***objects;

    float globalLighting;
};