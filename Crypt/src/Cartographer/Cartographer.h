#ifndef CARTOGRAPHER_H
#define CARTOGRAPHER_H

#include <vector>
#include <string>

#include "Config.h"

#include "Region.h"

class Cartographer
{
public:
	Cartographer();
	~Cartographer();

	Region* getRegion(int, int);

private:
	std::map<int, std::map<int,Region*> > _regions;
	
	Region* genRegion(int, int);

	int _x;
	int _y;
};

#endif // CARTOGRAPHER_H
