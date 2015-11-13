
#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Region.h"
#include "Plains.h"

#include "Tile.h"

#include "House.h"

Plains::Plains() {}
Plains::Plains(float density): Region(density, "Plains")
{
	// Set standard background tile, with random chance of ocassional tree
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

	INFO("Generated Plains");
}
