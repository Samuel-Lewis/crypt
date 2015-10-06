//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/lunchbox
//
//	@Project:	Lunchbox Toolset
//
//	@Last Updated:	2015-09-30 13:47:20
//	@Created:		2015-07-14 21:26:08
//
//===============================================//

#ifndef _LB_RNG_H
#define _LB_RNG_H

#include <random>
#include <cmath>
#include <iostream>

#define TIME_OUT 100

class lbRNG
{
public:
	template<typename T>
	static T linear(T,T);

	template <typename T>
	static T normDist(T,T);

	template <typename T>
	static T normDist(T,T,T,T);

};

// LINEAR
template <typename T>
T lbRNG::linear(T lower, T upper)
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_real_distribution<> distribution(lower, upper);

	T randNum = distribution(generator);

	return randNum;

}

// NORMAL DISTRIBUTION
template <typename T>
T lbRNG::normDist(T mean, T stdDev)
{
	// Using C++ random engine
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::normal_distribution<> distribution(mean, stdDev);

	T randNum = distribution(generator);

	return randNum;
}

template <typename T>
T lbRNG::normDist(T mean, T stdDev, T lower, T upper)
{
	// Using C++ random engine
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::normal_distribution<> distribution(mean, stdDev);

	T randNum = distribution(generator);
	for (int i = 0; i < TIME_OUT; i++)
	{
		// Not in while loop, because if user doesn't make the right range, we can't just inifite loop.
		if (randNum <= lower || randNum >= upper)
		{
			// Make sure we are in the designated range. Else get the number again.
			randNum = distribution(generator);
		} else {
			break;
		}
	}

	return randNum;
}

#endif //_LB_RNG_H
