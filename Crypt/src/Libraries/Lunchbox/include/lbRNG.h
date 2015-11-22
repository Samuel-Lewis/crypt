
//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/lunchbox
//
//	@Project:	Lunchbox Toolset
//
//	@Last Updated:	2015-11-22 19:23:27
//	@Created:		2015-07-14 21:26:08
//
//===============================================//

#ifndef _LB_RNG_H
#define _LB_RNG_H

#include <string>
#include <random>

class lbRNG
{
public:

	// SEED SETTERS / GETTERS
	static std::string generateSeed(std::string seedStr)
	{
		_seedStr = seedStr;
		std::seed_seq seed(seedStr.begin(), seedStr.end());
		_eng.seed(seed);

		return _seedStr;
	}

	static std::string generateSeed()
	{
		// Random number to string, to use as seed
		std::random_device rd;
		return generateSeed(std::to_string(rd()));
	}

	static std::string getSeed()
	{
		if (_seedStr == "")
		{
			generateSeed();
		}

		return _seedStr;
	}

	// RAW NUMBER GENERATORS
	template<typename T>
	static T linear(T lower, T upper)
	{
		getSeed();
		std::uniform_real_distribution<> dist(lower, upper);
		return dist(_eng);
	}

	template <typename T>
	static T normDist(T mean, T stdDev)
	{
		getSeed();
		std::normal_distribution<> dist(mean, stdDev);
		return dist(_eng);
	}

	// DEPENDANT CHANCES
	static bool decision(float weight)
	{
		return linear(0.0,1.0) < weight;
	}

private:
	lbRNG();
	~lbRNG();

	static std::string _seedStr;
	static std::default_random_engine _eng;
};

// Static vars
std::string lbRNG::_seedStr;
std::default_random_engine lbRNG::_eng;

#endif // _LB_RNG_H
