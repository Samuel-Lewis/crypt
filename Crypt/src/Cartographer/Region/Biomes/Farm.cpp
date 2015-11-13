
#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Tile.h"

#include "Region.h"
#include "Farm.h"

#include "Feature.hpp"


Farm::Farm() {}
Farm::Farm(float density): Region(density, "Farm")
{
	for (int x = 0; x < REGIONSIZE; x++)
	{
		for (int y = 0; y < REGIONSIZE; y++)
		{
			if (lbRNG::linear(0.0,1.0) < 0.03)
			{
				replace(x,y, new Tile("grass-light","tree-light"));
			} else {
				replace(x,y, new Tile("grass-light"));
			}
			
		}
	}
	
	Feature barn(5,5);
	barn.addBorder("floor-wood-light","wall-wood-light");
	
	replace(3,3,barn.tiles,true);
	
	
	INFO("Generated Farm");
}
