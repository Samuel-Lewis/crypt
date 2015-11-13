#ifndef REGION_BIOMES_FOREST_H
#define REGION_BIOMES_FOREST_H

#include "Config.h"

#include "Region.h"

// Heavily relies on CellAuto (only in .cpp)

class Forest: public Region
{
public:
	Forest();
	Forest(float);
	~Forest();
	
};

#endif // REGION_BIOMES_FOREST_H
