#include <iostream>
#include <vector>

#include "Config.h"
#include "lbLog.h"

#include "Region.h"

#include "Tile.h"
#include "Entity.h"

Region::Region() {}

Region::Region(float density, std::string newName)
{
	INFO("Generating new Region");
	_name = newName;
    _density = density;

	// Resize to default tile. All of these tiles will be replaced in some generator or another
	_map.resize( REGIONSIZE, std::vector<Tile*>( REGIONSIZE, new Tile()));
}

Region::Region(float density) : Region(density,"")
{}

Region::~Region()
{
	// TODO: Proper deletion
}

// Paint over one tile. Doesn't care if special or not
void Region::replace(int x, int y, Tile* newTile)
{
	// Bounds check
	if (x >= 0 && x < REGIONSIZE && y >=0 && y < REGIONSIZE)
	{
		// TODO: Delete the old tile (such that things don't break)
		_map[x][y] = newTile;
	}
}

// Paint a region, careing about specials
bool Region::replace(int startX, int startY, TILEGRID newArea, bool ignoreSpecial)
{
	TILEGRID savedMap = _map;
	
	for (int x = 0; x < (int)newArea.size(); x++)
	{
		for (int y = 0; y < (int)newArea[x].size(); y++)
		{
			if (newArea[x][y] == nullptr)
			{
				WARN("Tried to paint a null tile");
			} else {
				// TODO: Comparison on specials. Or scrap it all together
				replace(x+startX,y+startY,newArea[x][y]);
			}
		}
	}

	// Successful paint!
	return true;
}

// Connected textures
void Region::connectTextures()
{
	for (int x = 0; x < REGIONSIZE; x++)
	{
		for (int y = 0; y < REGIONSIZE; y++)
		{
			// GROND connections
			Entity::contType cont = _map[x][y]->getGround()->getContType();
			_map[x][y]->getGround()->setTextureName(_map[x][y]->getGround()->getEntityName());
			
			// Set texture prefix for ground
			if (cont == Entity::SOLID)
			{
				// Check if N,S,E,W are solid
				_map[x][y]->getGround()->setTextureSuffix(getNeighSuffix(x,y, [&](int newX, int newY)->bool
				{
					return _map[newX][newY]->isSolid();
				}	));
			} else if (cont == Entity::SELF) {
				// Check if N,S,E,W are the same
				_map[x][y]->getGround()->setTextureSuffix(getNeighSuffix(x,y, [&](int newX, int newY)->bool {
					return _map[newX][newY]->getGround()->getEntityName() == _map[x][y]->getGround()->getEntityName();
				}	));
			}
			
			// PROP connections
			cont = _map[x][y]->getProp()->getContType();
			_map[x][y]->getProp()->setTextureName(_map[x][y]->getProp()->getEntityName());
			
			if (cont == Entity::SOLID)
			{
				// Check if N,S,E,W are solid
				_map[x][y]->getProp()->setTextureSuffix(getNeighSuffix(x,y, [&](int newX, int newY)->bool
				{
					return _map[newX][newY]->isSolid();
				}	));
			} else if (cont == Entity::SELF) {
				// Check if N,S,E,W are the same
				_map[x][y]->getProp()->setTextureSuffix(getNeighSuffix(x,y, [&](int newX, int newY)->bool
				{
					return _map[newX][newY]->getProp()->getEntityName() == _map[x][y]->getProp()->getEntityName();
				}	));
			}
		}
	}
}

std::string Region::getNeighSuffix(int x, int y, std::function<bool(int,int)> check)
{
	int calc = 0;
	
	// Assign each cardinal a binary value, and add if present
	if (y > 0) calc += check(x,y-1) ? 1 : 0; // N
	if (x > 0) calc += check(x-1,y) ? 2 : 0; // W
	if (x < REGIONSIZE-1) calc += check(x+1,y) ? 4 : 0; // E
	if (y < REGIONSIZE-1) calc += check(x,y+1) ? 8 : 0; // S
	
	// Look up binary to tile position
	switch (calc)
	{
		case 0  : return "";
		case 1  : return "--s";
		case 2  : return "--e";
		case 3  : return "--se";
		case 4  : return "--w";
		case 5  : return "--sw";
		case 6  : return "--we";
		case 7  : return "--ss";
		case 8  : return "--n";
		case 9  : return "--ns";
		case 10 : return "--ne";
		case 11 : return "--ee";
		case 12 : return "--nw";
		case 13 : return "--ww";
		case 14 : return "--nn";
		case 15 : return "--centre";
		default : ERROR("Some how messed up getNeighSuffix calc"); return "";
			
	}
	
}


// Tile getter
Tile* Region::getTileAt(int x, int y)
{
	if (x >= 0 && x < REGIONSIZE && y >= 0 && y < REGIONSIZE)
	{
		return _map[x][y];
	} else {
		FATAL("Tried to getTileAt(" << x << "," << y << "), but it was out of bounds.");
		return nullptr;
	}
	
}

std::string Region::getRegionName()
{
	return _name;
}
