#include <string>
#include <vector>

#include "BiomeManager.hpp"

#include "lbLog.h"
#include "lbRNG.h"
#include "SimplexNoise.h"

#include "Cartographer.h"
#include "Region.h"

#include "Plains.h"
#include "Forest.h"

Cartographer::Cartographer()
{
    INFO("Starting new world...");
    _x = 0;
    _y = 0;

    getRegion(_x,_y);

    INFO("Generated new world!");
}

Cartographer::~Cartographer() {}


std::string Cartographer::getCurrentPrint()
{
    return _regions[_x][_y]->getPrint();
}

Region* Cartographer::getRegion(int x, int y)
{
    if (_regions[x].find(y) == _regions[x].end())
    {
        INFO("No region found at (" << x << "," << y << ")");
        // Map not found. Need to ini new one.

        GDict* biome = BiomeManager::getInstance().getBiomeFromTemp(scaled_raw_noise_2d(0,BiomeManager::getInstance().getMaxTemp(),x,y));
        if (biome == nullptr)
        {
            FATAL("i suck")
        }

        if (GStringFromDict(biome, "name") == nullptr)
        {
            FATAL("u suk");
        }

        std::string biomeName = GStringFromDict(biome, "name")->value;

        if (biomeName == "Plains")
        {
            _regions[x][y] = new Plains(32,32);
        } else if (biomeName == "Forest") {
            _regions[x][y] = new Forest(32,32);
        }
    }

    return _regions[x][y];
}
