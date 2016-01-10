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
	_target = _currentTile;
	
	
	_route = {_currentTile,_target,_calcPathTo(_target->x(), _target->y())};
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
	
	INFO("Plotting path to tile");
	Tile* origin = _currentTile;
	
	std::queue<Tile*> frontier;
	frontier.push(origin);
	
	std::map<Tile*, Tile*> from;
	from[origin] = origin;
	
	// Find the paths to the end point
	while (!frontier.empty())
	{
		Tile* curr = frontier.front();
		frontier.pop();
		
		// Check if target
		if (curr->x() == x && curr->y() == y)
		{
			
			// If target is solid, you want to remove that final 'step into' move
			if (_map[x][y]->isSolid() || _map[x][y]->hasMob())
			{
				INFO("Target is solid, remove final step");
				from.erase(std::prev(from.end()));
			}
			
			INFO("Collating steps");
			
			// Collate steps
			std::vector<Tile*> pathTiles;
			curr = _map[x][y];
			pathTiles.push_back(curr);
			
			while (curr != origin)
			{
				curr = from[curr];
				pathTiles.push_back(curr);
			}
			
			std::reverse(pathTiles.begin(), pathTiles.end());
			
			INFO("Made path");
			
			return pathTiles;
		}
		
		// Loop through the neighbours of current search
		for (auto const& neigh : curr->neighbours)
		{
			// Check if solid, and that we haven't visisted it
			if(!neigh.second->isSolid() && !from.count(curr))
			{
				frontier.push(neigh.second);
				from[neigh.second] = curr;
			}
		}
	}
	
	std::vector<Tile*> dud = {origin};
	
	return dud;	
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
				_target = targTile;
				_targetMoves = false;
				_route = {_currentTile,_target,_calcPathTo(_target->x(), _target->y())};
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
				_target = _map[x][y];
				_targetMoves = true;
				_route = {_currentTile,_target,_calcPathTo(_target->x(), _target->y())};
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
	if (_targetMoves)
	{
		_route = {_currentTile,_target,_calcPathTo(_target->x(), _target->y())};
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
	if (_targetMoves)
	{
		_route = {_currentTile,_target,_calcPathTo(_target->x(), _target->y())};
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
