
#ifndef REGION_GENERATOR_CELLAUTO_H
#define REGION_GENERATOR_CELLAUTO_H

#include <vector>
#include <string>

#include "Config.h"

#include "Tile.h"

class CellAuto
{
public:
	struct Options
	{
		// Gosh darn long constructor
		Options(int h, int w, int i, float aC, int dL, int bL, bool b) : height(h), width(w), iterations(i), aliveChance(aC), deathLimit(dL), birthLimit(bL), borders(b) {}
		int height; // Region height
		int width; // Region width
		int iterations; // Number of times to apply the step (the rules)
		float aliveChance; // Chance of starting alive at first gen
		int deathLimit; // Minimum number of alive adjacent cells to live
		int birthLimit; // Minimum number of alive adjacent cells to birth
		bool borders; // Whether to consider borders alive or dead
	};

	static TILEGRID generate(std::string, std::string, std::string, Options);
	static TILEGRID generate(std::string, std::string, Options);

private:
	CellAuto();
	~CellAuto();

	static void populateMap(std::vector< std::vector<bool> >&, Options);
	static int countAliveAdj(std::vector< std::vector<bool> >, int, int, Options);
	static std::vector< std::vector<bool> > step(std::vector< std::vector<bool> >, Options);
	
};

#endif // REGION_GENERATOR_CELLAUTO_H
