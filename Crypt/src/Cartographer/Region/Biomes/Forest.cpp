
#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Tile.h"
#include "CellAuto.h"

#include "Region.h"
#include "Forest.h"


Forest::Forest() {}
Forest::Forest(int newWidth, int newHeight, float density): Region(newWidth, newHeight, density, "Forest")
{
	// Setting options for CellAuto
	// height, width, iterations, alive chance, deathLimit, birthLimit, borders are walls
	CellAuto::Options opt(height(),width(),1,0.3 + 0.4*density,4,4,false);

	TILEGRID map = CellAuto::generate("tree-light","grass-light", getRegionName(),opt);

	// Replace the tiles, as if we'd done all the work ;)
	for (int x = 0; x < width(); x++)
	{
		for (int y = 0; y < height(); y++)
		{
			replace(x,y, map[x][y]);
		}
	}

	INFO("Generated Forest");
}
