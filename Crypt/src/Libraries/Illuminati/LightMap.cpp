#include "LightMap.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "TextManager.hpp"

LightMap::LightMap(Dimension _dim)
{
    dim = _dim;
    map = new float*[dim.width];
    objects = new MapObject**[dim.width];
    for (int i = 0; i < dim.width; ++i)
    {
        map[i] = new float[dim.height];
        objects[i] = new MapObject*[dim.height];
    }
}

LightMap::~LightMap()
{
    for (int i = 0; i < dim.width; ++i)
    {
        delete[] map[i];
        for (int j = 0; j < dim.height; ++j)
        {
            delete objects[i][j];
        }
        delete[] objects[i];
    }
    delete[] map;
    delete[] objects;
}

float LightMap::valueAt(int x, int y)
{
    return map[x][y];
}

void LightMap::calculate(int phase)
{
    setGlobalLighting(globalLighting);

    // loop over every object in the map
    for (int i = 0; i < dim.width; ++i)
    {
        for (int j = 0; j < dim.height; ++j)
        {
            if (dynamic_cast<LightSource *>(objects[i][j]) != nullptr)
            {
                LightSource *ls = dynamic_cast<LightSource *>(objects[i][j]);
                float intensity = ls->intensity;
                float radius = ls->dim.radius;

                map[i][j] += intensity;

                // loop over every pos in the map to do lighting
                for (int x = 0; x < dim.width; ++x)
                {
                    for (int y = 0; y < dim.height; ++y)
                    {
                        float dist = sqrtf(powf(std::abs(x - i), 2) + powf(std::abs(y - j), 2));

                        const float gradient = intensity/radius;

                        /*
                        printScreen("_____________________");
                        printScreen("x: " + std::to_string(x));
                        printScreen("x: " + std::to_string(y));
                        printScreen("grad: " + std::to_string(gradient));
                        printScreen("dist: " + std::to_string(dist));
                        printScreen("intensity: " + std::to_string(intensity));
                        printScreen("rad: " + std::to_string(radius));
                         */

                        for (float r = 0; r < radius; ++r)
                        {
                            float pulse = (gradient/radius)*sinf(phase);
                            if (dist >= r && dist <= (r+1))
                            {
                                float gray = std::abs((intensity - r*gradient)+pulse);

                                gray = gray > intensity ? intensity : gray;
                                float lum = map[x][y];
                                lum += gray;
                                lum = lum + gray > 1.0 ? 1.0 : lum + gray;
                                //printScreen("gray: " + std::to_string(gray));
                                map[x][y] = lum;
                            }
                        }
                    }
                }
            }
        }
    }
}

void LightMap::removeLightSource(LightSource *l)
{
    objects[l->dim.x][l->dim.y] = new BlockingObject(false, Dimension {l->dim.x,l->dim.y});
}

void LightMap::addLightSource(LightSource *l)
{
    delete objects[l->dim.x][l->dim.y];
    objects[l->dim.x][l->dim.y] = l;
}

void LightMap::addBlockingSource(BlockingObject *b)
{
    delete objects[b->dim.x][b->dim.y];
    objects[b->dim.x][b->dim.y] = b;
}

void LightMap::setGlobalLighting(float l)
{
    globalLighting = l;
    for (int i = 0; i < dim.width; ++i)
    {
        for (int j = 0; j < dim.height; ++j)
        {
            map[i][j] = l;
        }
    }
}

void LightMap::fillMapEmpty()
{
    for (int i = 0; i < dim.width; ++i)
    {
        for (int j = 0; j < dim.height; ++j)
        {
            objects[i][j] = new BlockingObject(false, Dimension {i, j});
        }
    }
}
