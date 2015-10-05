#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>

#include "../Tile.h"

class Region
{
public:
	Region();
	Region(int, int);
	Region(int, int, std::string);
	~Region();

	Tile* getTileAt(int, int);

	// Region painting
	void replace(int, int, Tile*);
	bool replace(int, int, Region*, bool);
	// bool replace(int, int, TILEGRID, bool);

	std::string getPrint();
	
	// Getters
	int width();
	int height();
	std::string getRegionName();

protected:
	std::vector<Region*> _features;

private:
	TILEGRID _map;

	int _width;
	int _height;

	std::string _name;
};

#endif // REGION_H
