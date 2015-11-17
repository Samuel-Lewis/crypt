#include "LightMap.h"

#define loop(__LOOP_VAR__, __LOOP_START__, __LOOP_END__) for (int __LOOP_VAR__ = __LOOP_START__; __LOOP_VAR__ < __LOOP_END__; ++__LOOP_VAR__)

#define loopi(__LOOP_START__, __LOOP_END__) loop(i, __LOOP_START__, __LOOP_END__)
#define loopj(__LOOP_START__, __LOOP_END__) loop(j, __LOOP_START__, __LOOP_END__)

#define loopij(__LOOP_START_I__, __LOOP_END_I__, __LOOP_START_J__, __LOOP_END_J__) loopi(__LOOP_START_I__, __LOOP_END_I__) loopj(__LOOP_START_J__, __LOOP_END_J__)

#include <cstdlib>
#include <cmath>

LightMap::LightMap(Dimension _dim)
{
    dim = _dim;
    map = new float*[dim.width];
    objects = new MapObject**[dim.width];
    loopi(0, dim.width)
    {
        map[i] = new float[dim.height];
        objects[i] = new MapObject*[dim.height];
    }
}

LightMap::~LightMap()
{
    loopi(0, dim.width)
    {
        delete[] map[i];
        loopj(0, dim.height)
        {
            delete objects[i][j];
        }
        delete[] objects[i];
    }
    delete[] map;
    delete[] objects;
}

void LightMap::calculate(int phase)
{
    // loop over every object in the map
    loopij(0, dim.width, 0, dim.height)
    {
        if (dynamic_cast<LightSource *>(objects[i][j]) != nullptr)
        {
            LightSource *ls = dynamic_cast<LightSource *>(objects[i][j]);
            float intensity = ls->intensity;
            float radius = ls->dim.radius;

            // loop over every pos in the map to do lighting
            loop(x, 0, dim.width)
            {
                loop(y, 0, dim.height)
                {
                    float dist = sqrtf(powf(std::abs(x - i), 2) + powf(std::abs(y - j), 2));

                    const int gradient = intensity/radius;

                    for (int r = 1; r < radius; r++)
                    {
                        float pulse = sinf(phase);
                        if (dist > r && dist < (r+2))
                        {
                            int gray = std::abs((intensity - r*gradient)+pulse);

                            gray = gray > intensity ? intensity : gray;
                            map[x][y] += gray;
                        }
                    }
                }
            }
        }
    }
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
    loopij(0, dim.width, 0, dim.height)
    {
        map[i][j] = l;
    }
}

void LightMap::fillMapEmpty()
{
    loopij(0, dim.width, 0, dim.height)
    {
        objects[i][j] = new BlockingObject(false, Dimension {i, j});
    }
}