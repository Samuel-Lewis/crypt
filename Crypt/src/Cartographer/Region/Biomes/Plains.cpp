
#include "lbLog.h"
#include "lbRNG.h"

#include "../Region.h"
#include "Plains.h"

#include "../../Tile.h"

#include "../Features/Buildings/House.h"

Plains::Plains() {}
Plains::Plains(int newWidth, int newHeight): Region(newWidth, newHeight, "Plains")
{
	// Set standard background tile, with random chance of ocassional tree
	for (int x = 0; x < width(); x++)
	{
		for (int y = 0; y < height(); y++)
		{
			if (lbRNG::linear(0.0,1.0) < 0.03)
			{
				replace(x,y, new Tile("Tree", false, getRegionName()));
			} else {
				replace(x,y, new Tile("Grass", false, getRegionName()));
			}

            // start a farm
            if (lbRNG::normDist(0.0, 1.0) > 2.6)
            {
                replace(x, y, new Tile("Field", true, getRegionName()));
            }

            //continue a farm
            //todo : replace with perlin noise
            if (lbRNG::normDist(0.0, 1.0) > 0.2
                    && (getTileAt(x > 1 ? x-1 : x, y)->getName() == "Field"
                    || getTileAt(x, y > 1 ? y-1 : y)->getName() == "Field"))
            {
                replace(x, y, new Tile("Field", true, getRegionName()));
            }
		}
	}


	// Chuck in a house or two for good measure
	for (int i = 0; i < lbRNG::normDist(2,1,0,4); i++)
	{
		House* house = new House;
		// Keep trying to add the house
		while (!replace(lbRNG::linear(0,width() - house->width()), lbRNG::linear(0,height() - house->height()), house, false)) {};
		_features.push_back(house);
		
	}

	INFO("Generated Plains");
}
