
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

	std::vector<Tile*> findMobTiles();
	
	bool setTarget(Tile*);
	bool setTarget(Entity*);
	
	DIRECTION step();
	DIRECTION peek();
	
	void setCurrentTile(Tile*);
	
	// Roam
	void setRoam();
	void setRoam(int,int, int);
	void setRoam(int,int,int,int);
	
protected:
	
	TILEGRID _map;
	
	Tile* _currentTile;
	Tile* _targetTile;
	Entity* _targetEnt;
	bool _targetMoves;
	
	struct Route
	{
		Tile* origin;
		Tile* end;
		std::vector<Tile*> pathTo;
	};
	
	Route _route;
	
	std::vector<Tile*> _calcPathTo(int,int);
	
};

#endif // PATH_H