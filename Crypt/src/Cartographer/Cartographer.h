#ifndef CARTOGRAPHER_H
#define CARTOGRAPHER_H

#include <vector>
#include <string>

#include "Region/Region.h"

class Cartographer
{
public:
	Cartographer();
	~Cartographer();

	std::string getCurrentPrint();

	Region* getRegion(int, int);

private:
	std::map<int, std::map<int,Region*> > _regions;

	int _x;
	int _y;

};

#endif // CARTOGRAPHER_H
