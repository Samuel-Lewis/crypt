#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <utility>

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
	_targetEnt = nullptr;

	_route = {_currentTile,_currentTile,{_currentTile}};
}

Path::~Path()
{}

// Returns a list of tiles in order of path distance away, that contain mobs
std::vector<Mob*> Path::findNearestMobs()
{
	INFO("Finding all mobs in region");
	// Get a list of all the mobs and their distances away
	std::vector<std::pair<int, Mob*>> routes;
	
	for (int x = 0; x < REGIONSIZE; x++)
	{
		for (int y = 0; y < REGIONSIZE; y++)
		{
			if (_map[x][y]->hasMob())
			{
				std::vector<Tile*> routeTo = _getRouteTo(_map[x][y]);
				
				routes.push_back(std::make_pair(routeTo.size(), _map[x][y]->getMob()));
			}
		}
	}
	
	// Remove any routes that are distance 0. These are routes that are either itself, or unreachable places
	for (int i = 0; i < (int)routes.size(); i++)
	{
		if (routes[i].first <= 0)
		{
			routes.erase(routes.begin()+i);
		}
	}

	// Sort from smallest to largest distance away
	std::sort(routes.begin(), routes.end(), [](std::pair<int, Mob*> lhs, std::pair<int, Mob*> rhs){ return lhs.first < rhs.first; });
	
	std::vector<Mob*> nearestMobs;
	
	for (int i = 0; i < (int)routes.size(); i++)
	{
		nearestMobs.push_back(routes[i].second);
	}
	
	INFO(nearestMobs.size() << " accessible mobs found.");
	
	return nearestMobs;
	
}

std::vector<Tile*> Path::_getRouteTo(Tile* target)
{
	INFO("Calculating route from ("<< _currentTile->x() <<","<< _currentTile->x() <<") to ("<< target->x() <<","<< target->y() <<")");
	// Ini the 'frontier'. The edge of the searched area
	std::queue<Tile*> frontier;
	frontier.push(_currentTile);
	
	// The route to each tile. key = destination, value = how to get to destination
	// You get to the key from the value
	std::map<Tile*, Tile*> pathTo;
	pathTo[_currentTile] = _currentTile;
	
	// Populate the frontier, until we find target or we've checked all possible tiles
	while (!frontier.empty())
	{
		// Get a tile from the frontier
		Tile* curr = frontier.front();
		frontier.pop();
		
		if (curr == target)
		{
			break;
		} else {
			for (auto const& neigh : curr->neighbours)
			{
				// Check if the frontiers borders are not solid, and also that they haven't already been checked
				if (!neigh.second->isSolid() && !pathTo.count(neigh.second))
				{
					// If not checked (or solid), add to the frontier
					frontier.push(neigh.second);
					
					// Add the route to get said tile though
					pathTo[neigh.second] = curr;
				}
			}
		}
	}
	
	// Path to follow
	std::vector<Tile*> route;
	
	// Check if there is a path to our target. If there is, back track from target to origin following the pathTo's
	if (pathTo.count(target))
	{
		INFO("Found path to target");
		Tile* curr = target;
		route.push_back(target);
		
		while (curr != _currentTile)
		{
			curr = pathTo[curr];
			route.push_back(curr);
		}
		
		std::reverse(route.begin(), route.end());
		
		INFO("Constructed path to target, length " << route.size());
		
	} else {
		INFO("Could not find path to target.");
	}
	
	return route;
}



void Path::setCurrentTile(Tile* newTile)
{
	_currentTile = newTile;
}

void Path::setTarget(Tile* target)
{
	_route = {_currentTile, target, _getRouteTo(target)};
	
	_targetEnt = nullptr;
	_targetMoves = false;
}

void Path::setTarget(Entity* target)
{
	
	for (int x = 0; x < REGIONSIZE; x++)
	{
		for (int y = 0; y < REGIONSIZE; y++)
		{
			if (_map[x][y]->hasMob())
			{
				if (_map[x][y]->getMob() == target)
				{
					_route = {_currentTile, _map[x][y], _getRouteTo(_map[x][y])};
					
					_targetEnt = target;
					_targetMoves = true;
					
					break;
				}
			}
		}
	}
}

// Get the direction of the next move
DIRECTION Path::step()
{
	_map = *(_currentTile->getParentMap());
	
	if (_targetMoves && _targetEnt != nullptr)
	{
		setTarget(_targetEnt);
	}
	
	if (_route.routeTo.empty())
	{
		// Ended the route (or there was none in the first place)
		return NONE;
	}
	
	// Loop through the neighbours of current search
	for (auto const& neigh : _currentTile->neighbours)
	{
		// Check if solid, and that we haven't visisted it
		if(neigh.second == _route.routeTo.front())
		{
			_currentTile = _route.routeTo.front();
			_route.routeTo.erase(_route.routeTo.begin()); // pop_front
			
			return neigh.first;
		}
	}
	
	WARN("Next PATH step does not match surrounding tiles");
	return NONE;
	
}

// Look at the next step, but don't actually take it
DIRECTION Path::peek()
{
	Route backUp = _route;
	
	DIRECTION dir = step();
	_route = backUp;
	
	return dir;
}
