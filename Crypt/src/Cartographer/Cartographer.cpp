#include <string>
#include <vector>

#include "lbLog.h"
#include "lbRNG.h"

#include "Cartographer.h"
#include "Region/Region.h"

#include "Region/Biomes/Plains.h"
#include "Region/Biomes/Forest.h"

Cartographer::Cartographer()
{
	INFO("Starting new world...");
	_x = 0;
	_y = 0;
		
	getRegion(_x,_y);

	INFO("Generated new world!");
}

Cartographer::~Cartographer() {}


std::string Cartographer::getCurrentPrint()
{
	return _regions[_x][_y]->getPrint();
}

Region* Cartographer::getRegion(int x, int y)
{
	if (_regions[x].find(y) == _regions[x].end())
	{
		INFO("No region found at (" << x << "," << y << ")");
		// Map not found. Need to ini new one.

        // choose a random one for now
        if (lbRNG::linear(0.0, 1.0) < 0.3)
        {
            _regions[x][y] = new Forest(32,32);
        }
        else
        {
            _regions[x][y] = new Plains(32,32);
        }
	}

	return _regions[x][y];
}
