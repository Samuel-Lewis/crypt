#include "BiomeManager.hpp"
#include "lbLog.h"

#include <fstream>
#include <cmath>

void BiomeManager::loadBiomesFromFile(std::string filename)
{
    // as we get these anytime, we need to keep the dict alive so load it in manually
    biomes = GArrayMake();
    std::ifstream tileFile(resourcePath() + filename);
    if (tileFile.good())
    {
        tileFile >> biomes;
    }
    tileFile.close();

    if (!biomes->good)
    {
        ERROR("BiomeManager failed to load");
    }
}

GDict *BiomeManager::getBiomeFromTemp(int temp)
{
    int foundTemp = 0;
    for (size_t i= 0; i < biomes->count(); ++i)
    {
        GDict *biome = GDictFromArray(biomes, i);

        foundTemp += GNumberFromDict(biome, "spread")->asInt();
        if (temp < foundTemp)
        {
            return biome;
        }
    }

    FATAL("Could not find biome from temperature: " << temp);

    return nullptr;
}

int BiomeManager::getMaxTemp()
{
    if (_maxTemp == -1) {
        
        for (size_t i= 0; i < biomes->count(); ++i)
        {
            GDict *biome = GDictFromArray(biomes, i);
            _maxTemp += GNumberFromDict(biome, "spread")->asInt();
        }
    }
    
    return _maxTemp;
}

float BiomeManager::getBiomeDensity(int temp)
{
    int foundTemp = 0;
    
    for (size_t i= 0; i < biomes->count(); ++i)
    {
        GDict *biome = GDictFromArray(biomes, i);
        
        if (temp < foundTemp)
        {
            // The closer the value is to the middle, the closer to 1 the density should be
            float spread = GNumberFromDict(biome, "spread")->asInt() / 2;
            return 1 - std::abs((spread - ((float)foundTemp - (float)temp))/spread);
            
           // return 1;
        
        } else {
            foundTemp += GNumberFromDict(biome, "spread")->asInt();
        }
        
    }
    
    WARN("Could not calculate density");
    
    return 1;
    
}

void BiomeManager::free()
{
    biomes->free();
}
