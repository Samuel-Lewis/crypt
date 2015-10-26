#include <vector>

#include "lbLog.h"
#include "lbRNG.h"

#include "../../Region.h"
#include "House.h"

#include "../../../Tile.h"

House::House(): House(lbRNG::normDist(7,1,5,10), lbRNG::normDist(7,1,5,10)) {}

House::House(int newWidth, int newHeight): Region(newWidth, newHeight, 1, "House")
{
	// Will pull walls from a vector (like a queue)
	std::vector<Tile*> walls;
	walls.resize(width()*2 + height()*2, new Tile("Wall", true, getRegionName()));

	// Randomly assign one wall as a door
	int doorPos = lbRNG::linear(1,width()*2 + height()*2 -1);
	while (doorPos != width() && doorPos!= height())
	{
		doorPos = lbRNG::linear(1,width()*2 + height()*2 -1);
	}

	// delete walls[doorPos];
	walls[doorPos] = new Tile("ClosedDoor");

	for (int x = 0; x < width(); x++)
	{
		// Add the interior floor
		for (int y = 0; y < height(); y++)
		{
			replace(x,y, new Tile("Path", true, "House"));
		}

		// Add top and bottom walls
		replace(x, 0, walls.back());
		walls.pop_back();
		replace(x, height()-1, walls.back());
		walls.pop_back();
	}


	// Add the side walls
	for (int i = 0; i < height(); i++)
	{
		replace(0, i, walls.back());
		walls.pop_back();
		replace(width()-1, i, walls.back());
		walls.pop_back();
	}



	INFO("Generated House");
}

House::~House() {}
