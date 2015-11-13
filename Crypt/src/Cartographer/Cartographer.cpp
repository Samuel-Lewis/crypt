#include <string>
#include <vector>

#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "BiomeManager.hpp"
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
		INFO("No region found at (" << x << "," << y << "). Generating new region...");
		// Map not found. Need to ini new one.
		
		_regions[x][y] = genRegion(x,y);
	}

    return _regions[x][y];
}

Region* Cartographer::genRegion(int x, int y)
{
	Region* newRegion;
	
	// Get temperatue of region/biome
	float temp = scaled_raw_noise_2d(0,BiomeManager::getInstance().getMaxTemp(),x,y);
	
	GDict* biome = BiomeManager::getInstance().getBiomeFromTemp(temp);
	float density = BiomeManager::getInstance().getBiomeDensity(temp);
	
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
		newRegion = new Plains(density);
	} else if (biomeName == "Forest") {
		newRegion = new Forest(density);
	} else if (biomeName == "Farm") {
		newRegion = new Farm(density);
	} else {
		WARN("Requested biome '" << biomeName << "'does not have a generator. Default to Plains");
		newRegion = new Plains(1);
	}
	
	newRegion->connectTextures();
	
	return newRegion;
}

