
#ifndef FEATURE_CELLAUTO_H
#define FEATURE_CELLAUTO_H

#include <vector>
#include <string>

#include "Config.h"

#include "lbLog.h"

#include "Feature.h"

class CellAuto: public Feature
{
public:
	
	CellAuto(int, int);
	virtual ~CellAuto();
	
	struct Options
	{
		// Gosh darn long constructor
		Options(int i, float aC, int dL, int bL, bool b) : iterations(i), aliveChance(aC), deathLimit(dL), birthLimit(bL), borders(b) {}
		int iterations; // Number of times to apply the step (the rules)
		float aliveChance; // Chance of starting alive at first gen
		int deathLimit; // Minimum number of alive adjacent cells to live
		int birthLimit; // Minimum number of alive adjacent cells to birth
		bool borders; // Whether to consider borders alive or dead
	} options;

	void generate(std::string, std::string);
	
private:
	
	void populateMap(std::vector< std::vector<bool> >&);
	int countAliveAdj(std::vector< std::vector<bool> >, int, int);
	std::vector< std::vector<bool> > step(std::vector< std::vector<bool> >);
	
};

#endif // FEATURE_CELLAUTO_H
