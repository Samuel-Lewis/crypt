//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/lunchbox
//
//	@Project:	Lunchbox Toolset
//
//	@Last Updated:	2015-10-19 18:27:45
//	@Created:		2015-07-14 21:26:08
//
//===============================================//

#ifndef _LB_RNG_H
#define _LB_RNG_H

#include <string>
#include <random>

namespace lbRNG
{

	// LINEAR
	template<typename T>
	T linear(T lower, T upper, std::string seedStr)
	{
		std::seed_seq seed(seedStr.begin(), seedStr.end());
		std::default_random_engine gen(seed);

		std::uniform_real_distribution<> dist(lower, upper);

		return dist(gen);
	}

	template<typename T>
	T linear(T lower, T upper)
	{
		// Generate some string from random numbers
		std::random_device rd;
		return linear(lower, upper, std::to_string(rd()));
	}

	// NORMAL DISTRIBUTION
	template <typename T>
	T normDist(T mean, T stdDev, std::string seedStr)
	{
		// Gen seed
		std::seed_seq seed(seedStr.begin(), seedStr.end());
		std::default_random_engine gen(seed);

		std::normal_distribution<> dist(mean, stdDev);

		return dist(gen);
	}

	template <typename T>
	T normDist(T mean, T stdDev)
	{
		// Generate some string from random numbers
		std::random_device rd;
		return normDist(mean, stdDev, std::to_string(rd()));
	}

}

#endif // _LB_RNG_H
