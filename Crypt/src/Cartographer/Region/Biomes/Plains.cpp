
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
	// Simple default region
	
	// Make some sort of background, just use default region for now
	Feature bg(REGIONSIZE, REGIONSIZE);
	
	bg.generate();
	
	// Paint 'dem tiles
	replace(0,0,bg.tiles);

	INFO("Generated Plains");
}
