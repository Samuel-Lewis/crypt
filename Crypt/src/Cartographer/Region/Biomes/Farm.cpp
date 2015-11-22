
#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Tile.h"

#include "Region.h"
#include "Farm.h"

#include "Feature.h"
#include "Field.h"

Farm::Farm() {}
Farm::Farm(float density): Region(density, "Farm")
{
	// Set standard background
	for (int x = 0; x < REGIONSIZE; x++)
	{
		for (int y = 0; y < REGIONSIZE; y++)
		{
			if (lbRNG::decision(0.3))
			{
				// Random tree or two
				replace(x,y, new Tile("grass-light","tree-light"));
			} else {
				replace(x,y, new Tile("grass-light"));
			}
			
		}
	}
	
	// Add Barn
	Feature barn(5,5);
	barn.setAllGround("floor-wood-light");
	barn.setBorderProp("wall-wood-light");
	barn.addDoor("door-wood-open","door-wood-closed", N);

	// Add fields
	Field field1(8,5);
	Field field2(4,9);
	
	field1.generate();
	field2.generate();
	
	field1.setBorderGround("dirt-light");
	field1.setBorderProp("fence-wood");
	field1.addDoor("air","air",N);
	field1.addDoor("air","air",S);
	
	// Place down new tiles
	replace(3,3,barn.tiles,true);
	replace(2,9,field1.tiles,true);
	replace(10,5,field2.tiles,true);
	
	INFO("Generated Farm");
}
