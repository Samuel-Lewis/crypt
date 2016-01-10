
#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Tile.h"

#include "Region.h"
#include "Farm.h"

#include "Feature.h"
#include "Field.h"

#include "Livestock.h"

Farm::Farm() {}
Farm::Farm(float density): Region(density, "Farm")
{
	// Set standard background
	for (int x = 0; x < REGIONSIZE; x++)
	{
		for (int y = 0; y < REGIONSIZE; y++)
		{
			if (lbRNG::decision(0.05))
			{
				// Random tree or two
				replace(x,y, new Tile("grass-light","tree-light"));
			} else {
				replace(x,y, new Tile("grass-light"));
				
				if (lbRNG::decision(0.01))
				{
					getTileAt(x, y)->setMob(new Sheep(getTileAt(x, y)));
					
				}
			}
			
		}
	}
	
	// Add Barn
	Feature barn(5,5);
	barn.addAll("floor-wood-light");
	barn.addBorder("wall-wood-light");
	barn.addDoor("door-wood-open","door-wood-closed", N);

	// Add fields
	Field field1(8,5);
	Field field2(4,9);
	
	field1.generate();
	field2.generate();
	
	field1.clearBorder();
	
	field1.addBorder("dirt-light");
	field1.addBorder("fence-wood");
	field1.addDoor("air","air",N);
	field1.addDoor("air","air",S);
	
	// Place down new tiles
	replace(3,3,barn.tiles);
	replace(2,9,field1.tiles);
	replace(10,5,field2.tiles);
	
	INFO("Generated Farm");
}
