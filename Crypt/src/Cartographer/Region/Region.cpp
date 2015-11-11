#include <iostream>
#include <vector>

#include "lbLog.h"

#include "Region.h"

#include "../Tile.h"

Region::Region() {}

Region::Region(int width, int height, float density, std::string newName)
{
	INFO("Generating new Region");
	_width = width;
	_height = height;
	_name = newName;
    _density = density;

	// Set at least some tile. Will appear blank.
	_map.resize( _width, std::vector<Tile*>( _height, new Tile()));
}

Region::Region(int width, int height): Region(width,height,1, "") {}

Region::~Region()
{
	// Probably delete something here...
}

// Paint over one tile. Doesn't care if special or not
void Region::replace(int x, int y, Tile* newTile)
{
	_map[x][y] = newTile;
}

// Paint a region. Cares about specials
bool Region::replace(int startX, int startY, Region* subRegion, bool ignoreSpecial)
{
	TILEGRID savedMap = _map;
	for (int x = 0; x < subRegion->width(); x++)
	{
		for (int y = 0; y < subRegion->height(); y++)
		{
			if (x >= 0 && x + startX < width() && y >= 0 && y + startY < height())
			{
				// Make sure not painting over specials
				if (getTileAt(x + startX, y + startY)->getSpecial() > subRegion->getTileAt(x,y)->getSpecial() && !ignoreSpecial)
				{
					// Revert back to map before any painting
					_map = savedMap;
					return false;
				} else {
					replace(x + startX, y + startY, subRegion->getTileAt(x,y));
				}
			}
		}
	}

	// Successful paint!
	return true;
}

// Tile getter
Tile* Region::getTileAt(int x, int y)
{
	if (x >= 0 && x < width() && y >= 0 && y < height())
	{
		return _map[x][y];
	} else {
		ERROR("Tried to getTileAt(" << x << "," << y << "), but it was out of bounds.");
	}
    return nullptr;
}

// Width and height getters
int Region::width()
{
	return _width;
}

int Region::height()
{
	return _height;
}

std::string Region::getRegionName()
{
	return _name;
}
