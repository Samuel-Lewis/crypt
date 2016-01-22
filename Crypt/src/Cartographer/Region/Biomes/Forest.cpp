
#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Tile.h"

#include "Region.h"
#include "Forest.h"

#include "CellAuto.h"


Forest::Forest() {}

Forest::Forest(float density): Region(density, "Forest")
{
	CellAuto ca(REGIONSIZE, REGIONSIZE);
	
	ca.options.iterations = 1;
	ca.options.aliveChance = 0.3 + 0.4*density;
	ca.options.deathLimit = 4;
	ca.options.birthLimit = 4;
	ca.options.borders = false;

	ca.generate("tree-light","grass-light");

	// Paint tiles onto region map
	replace(0,0,ca.tiles);
	
	INFO("Generated Forest");
}
