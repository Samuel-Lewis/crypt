#include <vector>
#include <queue>
#include <map>
#include <algorithm>

#include "lbLog.h"
#include "lbRNG.h"

#include "Config.h"

#include "Tile.h"
#include "Path.h"


Path::Path(Tile* startTile)
{
	// Get map ref, but the actual map
	_map = *(startTile->getParentMap());
	_currentTile = startTile;
	
	_targetMoves = false;
	_targetTile = _currentTile;
	_targetEnt = nullptr;
	
	
	_route = {_currentTile,_targetTile,{_currentTile}};
}

Path::~Path()
{}

// Returns a list of tiles in order of path distance away, that contain mobs
std::vector<Tile*> Path::findMobTiles()
{
	std::vector<Route> routes;
	
	// Find all the mobs on the map
	for (int x = 0; x < (int)(_map).size(); x++)
	{
		for (int y = 0; y < (int)(_map).size(); y++)
		{
			if (_map[x][y]->hasMob())
			{
				// Calculate the route
				routes.push_back({_currentTile,_map[x][y],_calcPathTo(x,y)});
			}
		}
	}
	
	// Sort from nearest to furthest (by length of path)
	std::sort(routes.begin(), routes.end(), [](Route lhs, Route rhs){ return lhs.pathTo.size() < rhs.pathTo.size(); });

	// Convert to just tiles
	std::vector<Tile*> tiles;

	for(int i = 0; i < (int)routes.size();i++)
	{
		tiles.push_back(routes[i].end);
	}
	
	return tiles;
}


// Uses A* to get a path of tiles from current position to a given x,y position
std::vector<Tile*> Path::_calcPathTo(int x, int y)
{

	// *sigh*
	// TODO: Fix A* pathfinding
	
	/*
	 * To consider:
	 *		Need to be able to check if route is actually possible
	 *		Make sure it's a reasonably short route
	 *
	 */

}

void Path::setCurrentTile(Tile* newTile)
{
	_currentTile = newTile;
}

bool Path::setTarget(Tile* targTile)
{
	for (int x = 0; x < (int)(_map).size(); x++)
	{
		for (int y = 0; y < (int)(_map).size(); y++)
		{
			if (targTile == _map[x][y])
			{
				_targetTile = targTile;
				_targetEnt = nullptr;
				_targetMoves = false;
				_route = {_currentTile,_targetTile,_calcPathTo(x, y)};
				return true;
			}
		}
	}
	
	INFO("Could not find given target tile in map");
	return false;
	
}

bool Path::setTarget(Entity* targEnt)
{
	for (int x = 0; x < (int)(_map).size(); x++)
	{
		for (int y = 0; y < (int)(_map).size(); y++)
		{
			std::vector<Entity*> ents = _map[x][y]->getEntities();
			if (std::find(ents.begin(), ents.end(), targEnt) != ents.end())
			{
				_targetTile = _map[x][y];
				_targetEnt = targEnt;
				_targetMoves = true;
				_route = {_currentTile,_targetTile,_calcPathTo(x, y)};
				return true;
			}
		}
	}
	
	INFO("Could not find given target entity in map");
	return false;
}

// Get the direction of the next move
DIRECTION Path::step()
{
	if (_targetMoves && _targetEnt != nullptr)
	{
		setTarget(_targetEnt);
	}
	
	if (_route.pathTo.empty())
	{
		// Ended the route (or there was none in the first place)
		return NONE;
	}
	
	
	Tile* destTile = _route.pathTo.front();
	
	// Loop through the neighbours of current search
	for (auto const& neigh : _currentTile->neighbours)
	{
		// Check if solid, and that we haven't visisted it
		if(neigh.second == destTile)
		{
			_currentTile = destTile;
			_route.pathTo.erase(_route.pathTo.begin()); // pop_front
			
			return neigh.first;
		}
	}
	
	WARN("Next PATH step does not match surrounding tiles");
	return NONE;
	
}

// Look at the next step, but don't actually take it
DIRECTION Path::peek()
{
	if (_targetMoves && _targetEnt != nullptr)
	{
		setTarget(_targetEnt);
	}
	
	Route backUp = _route;
	
	DIRECTION dir = step();
	_route = backUp;
	
	return dir;
}


// Roaming presets
void Path::setRoam(int x, int y, int width, int height)
{
	
	setTarget(_map[lbRNG::linear(x,width)][lbRNG::linear(y,height)]);
}

void Path::setRoam()
{
	setRoam(0,0,REGIONSIZE-1, REGIONSIZE-1);
}
