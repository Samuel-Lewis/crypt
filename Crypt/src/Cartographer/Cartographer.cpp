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
#include "Farm.h"

Cartographer::Cartographer()
{
    INFO("Starting new world...");
    _x = 0;
    _y = 0;

    getRegion(_x,_y);

    INFO("Generated new world!");
}

Cartographer::~Cartographer() {}


Region* Cartographer::getRegion(int x, int y)
{
    if (_regions[x].find(y) == _regions[x].end())
    {
        INFO("No region found at (" << x << "," << y << ")");
        // Map not found. Need to ini new one.

        // Get temperatue of region/biome
        float temp = scaled_raw_noise_2d(0,BiomeManager::getInstance().getMaxTemp(),x,y);
        
        GDict* biome = BiomeManager::getInstance().getBiomeFromTemp(temp);
        float density = BiomeManager::getInstance().getBiomeDensity(temp);
        
        INFO("Density: " << density);
        
        if (biome == nullptr)
        {
            FATAL("Requested biome out of temperature bounds.");
        }

        if (GStringFromDict(biome, "name") == nullptr)
        {
            FATAL("Biome did not have defined name.");
        }

        std::string biomeName = GStringFromDict(biome, "name")->value;

        // Biome name to class look up table
        if (biomeName == "Plains")
        {
            _regions[x][y] = new Plains(32,32,density);
        } else if (biomeName == "Forest") {
            _regions[x][y] = new Forest(32,32,density);
        } else if (biomeName == "Farm") {
            _regions[x][y] = new Farm(32,32,density);
        } else {
            WARN("Requested biome '" << biomeName << "'does not have a generator. Default to Plains");
            _regions[x][y] = new Plains(32,32,1);
        }
    }

    return _regions[x][y];
}
