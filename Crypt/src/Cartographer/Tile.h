
#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>

#include "lbCSV.h"

class Tile
{
public:
	Tile();
	Tile(std::string);
	Tile(std::string, bool);
	Tile(std::string, bool, std::string);
	~Tile();

	std::string getIcon();
	bool isSolid();
	std::string getName();

	void setSpecial(bool);
	bool isSpecial();

private:

	std::string _name;
	std::string _icon;
	bool _solid;

	bool _special;

	std::string _regionName;

	// TABLE comes from lbCSV
	static TABLE _tileList;

	// Just for debugging
	static std::vector<std::string> unFoundTiles;

};

typedef std::vector< std::vector<Tile*> > TILEGRID;

#endif // TILE_H
