#include "LightMap.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "TextManager.hpp"

LightMap::LightMap(int w, int h)
{
    width = w;
    height = h;
    map = new int*[width];
    objects = new int*[width];
    for (int i = 0; i < width; ++i)
    {
        map[i] = new int[height];
        objects[i] = new int[height];
    }
}

LightMap::~LightMap()
{
    for (int i = 0; i < width; ++i)
    {
        delete[] map[i];
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

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            int o = objects[i][j];
            if (o > LEMPTY)
            {
                int intensity = intensityFromLightMask(o);
                int radius = radiusFromLightMask(o);

                map[i][j] = intensity;

                for (int edgeX = 0; edgeX < width; edgeX++)
                {
                    for (int edgeY = 0; edgeY < height; edgeY++)
                    {
                        if (edgeX == 0 || edgeY == 0 || edgeX == width-1 || edgeY == height-1)
                        {
                            std::vector<Point> line = rayTrace(i, j, edgeY, edgeX);

                            for (int l = 0; l < line.size(); ++l)
                            {
                                Point lp = line[l];
                                float dist = sqrtf(powf((lp.x - i), 2) + powf((lp.y - j), 2));
                                if (l > radius)
                                {
                                    break;
                                }

                                int g = intensity/((dist/2)*(l+1)) + radius*dist*sinf(phase) + radius*dist;
                                if (g > intensity)
                                {
                                    g = intensity;
                                }
                                else if (g < globalLighting)
                                {
                                    g = globalLighting;
                                }

                                if (objects[lp.x][lp.y] == LEMPTY)
                                {
                                    map[lp.x][lp.y] = g > map[lp.x][lp.y] ? g : map[lp.x][lp.y];
                                }
                                else if (objects[lp.x][lp.y] == LBLOCKING)
                                {
                                    map[lp.x][lp.y] = g > map[lp.x][lp.y] ? g : map[lp.x][lp.y];
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Bresenham's line algorithm
std::vector<LightMap::Point> LightMap::rayTrace(int x0, int y0, int x1, int y1)
{
    std::vector<LightMap::Point> line;

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    while (true)
    {
        line.push_back(LightMap::Point {x0,y0});
        if (x0==x1 && y0==y1)
        {
            break;
        }
        e2 = err;
        if (e2 >-dx)
        {
            err -= dy; x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx; y0 += sy;
        }
    }

    return line;
}
void LightMap::addLightSource(int x, int y, int i, int r)
{
    int mask = createLightMask(i, r);
    objects[x][y] = mask;
}

void LightMap::addBlockingSource(int x, int y, bool s)
{
    objects[x][y] = s == true ? LBLOCKING : LEMPTY;
}

inline int LightMap::createLightMask(int i, int r)
{
    return i | (r << 8*sizeof(int)/2);
}

inline int LightMap::radiusFromLightMask(int m)
{
    return (m >> 8*sizeof(int)/2) & 0xFFFF;
}

inline int LightMap::intensityFromLightMask(int m)
{
    return m & 0xFFFF;
}

void LightMap::setGlobalLighting(int l)
{
    globalLighting = l;
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            map[i][j] = l;
        }
    }
}

void LightMap::fillMapEmpty()
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            objects[i][j] = LEMPTY;
        }
    }
}
