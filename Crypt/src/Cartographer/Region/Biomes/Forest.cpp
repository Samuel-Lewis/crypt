
#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Tile.h"
#include "CellAuto.h"

#include "Region.h"
#include "Forest.h"


Forest::Forest() {}
Forest::Forest(float density): Region(density, "Forest")
{
	// Setting options for CellAuto
	// height, width, iterations, alive chance, deathLimit, birthLimit, borders are walls
	CellAuto::Options opt(REGIONSIZE,REGIONSIZE,1,0.3 + 0.4*density,4,4,false);

	TILEGRID map = CellAuto::generate("tree-light","grass-light", getRegionName(),opt);

	// Paint tiles onto region map
	replace(0,0,map);
	
	INFO("Generated Forest");
}
