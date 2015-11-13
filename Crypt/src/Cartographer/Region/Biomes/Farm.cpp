
#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Tile.h"

#include "Region.h"
#include "Farm.h"

#include "Feature.h"


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
	barn.addFloor("floor-wood-light");
	barn.addBorder("floor-wood-light","wall-wood-light");

	Feature field1(11,6);
	field1.addFloor("field-light");
	
	Feature field2(4,8);
	field2.addFloor("field-light");
	
	
	replace(3,3,barn.tiles,true);
	replace(2,9,field1.tiles,true);
	replace(9,5,field2.tiles,true);
	
	
	INFO("Generated Farm");
}
