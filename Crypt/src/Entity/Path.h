
#ifndef PATH_H
#define PATH_H

#include <vector>

#include "Config.h"

class Tile;
class Entity;
class Mob;

typedef std::vector< std::vector<Tile*> > TILEGRID;

class Path {
public:
	Path(Tile*);
	virtual ~Path();

	std::vector<Mob*> findNearestMobs();
	
	void setTarget(Tile*);
	void setTarget(Entity*);
	
	DIRECTION step();
	DIRECTION peek();
	
	void setCurrentTile(Tile*);
	
protected:
	
	TILEGRID _map;
	
	Tile* _currentTile;
	Entity* _targetEnt;
	bool _targetMoves;
	
	struct Route
	{
		Tile* origin;
		Tile* end;
		std::vector<Tile*> routeTo;
	};
	
	Route _route;
	
	std::vector<Tile*> _getRouteTo(Tile*);
	
};

#endif // PATH_H