#ifndef REGION_BIOMES_FARM_H
#define REGION_BIOMES_FARM_H

#include "Config.h"

#include "Region.h"

class Farm: public Region
{
public:
	Farm();
	Farm(int, int, float);
	~Farm();
	
};

#endif // REGION_BIOMES_FARM_H
