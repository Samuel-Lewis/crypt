#pragma once

#define LBLOCKING -1
#define LEMPTY 0

#include <vector>
#include <algorithm>

class LightMap
{
public:
    LightMap(int w, int h);
    ~LightMap();

    void setGlobalLighting(int l);
    void fillMapEmpty();

    float valueAt(int x, int y);

    void addLightSource(int x, int y, int i, int r);
    void addBlockingSource(int x, int y, bool s);

    void calculate(int phase);

    struct Point
    {
        int x;
        int y;
    };

    int width;
    int height;

private:
    static inline int createLightMask(int i, int r);
    static inline int radiusFromLightMask(int m);
    static inline int intensityFromLightMask(int m);

    std::vector<Point> rayTrace(int x0, int y0, int x1, int y1);

    int **map;
    int **objects;

    int globalLighting;
};