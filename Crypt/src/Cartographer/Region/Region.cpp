#include <iostream>
#include <vector>

#include "lbLog.h"

#include "Region.h"

#include "../Tile.h"

Region::Region() {}

Region::Region(int width, int height, std::string newName)
{
	INFO("Generating new Region");
	_width = width;
	_height = height;
	_name = newName;

	// Set at least some tile. Air will appear blank
	_map.resize( _width, std::vector<Tile*>( _height, new Tile("Air")));
}

Region::Region(int width, int height): Region(width,height, "") {}

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
				if (getTileAt(x + startX, y + startY)->isSpecial() && !ignoreSpecial)
				{
					// If we do paint over a special, cancel the whole process
					WARN("Some region tried to overwrite special tiles at " << x + startX << "," << y + startY);
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

// bool Region::replace(int startX, int startY, TILEGRID subGrid, bool ignoreSpecial)
// {
// 	for (unsigned x = 0; x < subGrid.size(); x++)
// 	{
// 		for (unsigned y = 0; y < subGrid.size(); y++)
// 		{
// 			if (x >= 0 && x + startX < subGrid.size() && y >= 0 && y + startY < subGrid[x].size())
// 			{
// if (getTileAt(x + startX, y + startY)->isSpecial())
// 				{
// 					// If we do paint over a special, cancel the whole process
// 					WARN("Some region tried to overwrite special tiles at " << x + startX << "," << y + startY);
// 					// Revert back to map before any painting
// 					_map = savedMap;
// 					return false;
// 				} else {
// 					replace(x + startX, y + startY, subRegion->getTileAt(x,y));
// 				}
// 			}
// 	// Successful paint!
// 	return true;
// }

// Tile getter
Tile* Region::getTileAt(int x, int y)
{
	if (x >= 0 && x < width() && y >= 0 && y < height())
	{
		return _map[x][y];
	} else {
		FATAL("Tried to getTileAt(" << x << "," << y << "), but it was out of bounds.");
	}
    return nullptr;
}

// Pretty printer
std::string Region::getPrint()
{
	std::string str = "";
	// Print fancy borders
	// For every tile
	for (int y = 0; y < height(); y++)
	{
		for (int x = 0; x < width(); x++)
		{
			// ANSI code + the icon
			// str += "\033[" + _map[x][y]->getFormat()+ "m"+ _map[x][y]->getIcon()+ "\033[0m";
			str += _map[x][y]->getIcon();
		}
	}

	// More pretty borders
	return str;
	INFO("Printed map");
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
