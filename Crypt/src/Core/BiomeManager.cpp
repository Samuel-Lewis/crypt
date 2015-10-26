#include "BiomeManager.hpp"
#include "lbLog.h"

#include <fstream>

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
        ERROR("tilemanger failed to load");
    }
}

GDict *BiomeManager::getBiomeFromTemp(int temp)
{
    int foundTemp = 0;

    for (size_t i= 0; i < biomes->count(); ++i)
    {
        GDict *biome = GDictFromArray(biomes, i);

        if (temp < foundTemp)
        {
            return biome;
        } else {
            foundTemp += GNumberFromDict(biome, "spread")->asInt();
        }
    }
    return nullptr;
}

int BiomeManager::getMaxTemp()
{
    int maxTemp = 0;

    for (size_t i= 0; i < biomes->count(); ++i)
    {
        GDict *biome = GDictFromArray(biomes, i);
        maxTemp += GNumberFromDict(biome, "spread")->asInt();
    }

    return maxTemp;
}

void BiomeManager::free()
{
    biomes->free();
}