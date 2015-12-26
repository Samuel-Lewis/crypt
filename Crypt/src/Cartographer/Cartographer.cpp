#include <string>
#include <vector>

#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Manager.h"
#include "SimplexNoise.h"

#include "Cartographer.h"
#include "Region.h"

#include "Plains.h"
#include "Forest.h"
#include "Farm.h"

Cartographer::Cartographer()
{
    INFO("Starting new world...");

    getRegion(0,0);

    INFO("Generated new world!");
}

Cartographer::~Cartographer() {}


Region* Cartographer::getRegion(int x, int y)
{
    if (_regions[x].find(y) == _regions[x].end())
    {
		INFO("No region found at (" << x << "," << y << ")");
		// Map not found. Need to ini new one.
		
		_regions[x][y] = genRegion(x,y);
	}

    return _regions[x][y];
}

Region* Cartographer::genRegion(int x, int y)
{
	INFO("Generating new region at (" << x << "," << y << ")...");
	Region* newRegion;
	
	// Get temperatue of region/biome
	float temp = scaled_raw_noise_2d(0,Manager::biome().getMaxTemp(),x,y);
	
    GDict* biome = Manager::biome().getBiomeFromTemp(temp);
	float density = Manager::biome().getBiomeDensity(temp);
	
	// Biome out of temp bounds
	if (biome == nullptr)
	{
		FATAL("Requested biome out of temperature bounds.");
	}
	
	// Biome doesn't exsit
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
	
	// Pretty up those textures and connect them
	newRegion->connectTextures();
	
	
	return newRegion;
}

