
#include "Config.h"

#include "lbLog.h"
#include "lbRNG.h"

#include "Region.h"
#include "Plains.h"

#include "Feature.h"

#include "Tile.h"

Plains::Plains() {}
Plains::Plains(float density): Region(density, "Plains")
{
	Feature bg(REGIONSIZE, REGIONSIZE);
	
	bg.generate();
	
	replace(0,0,bg.tiles,true);

	INFO("Generated Plains");
}
