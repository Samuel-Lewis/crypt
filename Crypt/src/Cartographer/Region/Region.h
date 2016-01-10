#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>

#include "Tile.h"
#include "Config.h"
#include "lbLog.h"


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
	void replace(int, int, TILEGRID);
	
	void paint(int, int, Tile*);
	void paint(int, int, TILEGRID);
	
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
