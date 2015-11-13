
#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Region.h"
#include "Plains.h"

#include "Tile.h"

#include "House.h"

Plains::Plains() {}
Plains::Plains(int newWidth, int newHeight, float density): Region(newWidth, newHeight, density, "Plains")
{
	// Set standard background tile, with random chance of ocassional tree
	for (int x = 0; x < width(); x++)
	{
		for (int y = 0; y < height(); y++)
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
