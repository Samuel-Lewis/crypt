#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>

#include "Config.h"
#include "lbLog.h"

#include "Tile.h"

class Region
{
public:
	Region();
	Region(float); // Density
	Region(float, std::string); // Density, name
	~Region();

	Tile* getTileAt(int, int);
	
	void connectTextures();

	// Region painting
	void replace(int, int, Tile*);
	bool replace(int, int, TILEGRID, bool);
	
	// Getters
	std::string getRegionName();

protected:
	std::vector<Region*> _features;
	
	std::string getNeighSuffix(int, int, std::function<bool(int,int)>);

private:
	TILEGRID _map;
	
	float _density;
	
	std::string _name;
};

#endif // REGION_H
