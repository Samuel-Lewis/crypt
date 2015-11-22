//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/lunchbox
//
//	@Project:	Lunchbox Toolset
//
//	@Last Updated:	2015-11-22 19:20:02
//	@Created:		2015-09-30 13:45:13
//
//===============================================//

// #define _LB_EXAMPLE
#ifdef _LB_EXAMPLE

#include <vector>

#include "../include/lbLog.h"
#include "../include/lbRNG.h"
#include "../include/lbString.h"
#include "../include/lbCSV.h"

int main()
{
	// ==== lbLog demo ==== //
	// Set debug levels to show all, log all, and quit on fatal
	lbLog::quickSet(lbLog::info, lbLog::all, lbLog::fatal);

	// Start the log in example/logs directory, named 'testlog-[timestamp].log'
	lbLog::startLog("example/logs/","testlog",true);

	// ==== lbRNG demo ==== //
	// INFO(lbRNG::generateSeed("custom seed string"));
	INFO("A random number between 0 and 10 is " << lbRNG::linear(0,10));
	INFO("A random number between 0 and 10 is " << lbRNG::linear(0,10));
	INFO("A normally distributed N(5,2)" << lbRNG::normDist(5,2));

	INFO("Seed: " << lbRNG::getSeed())

	// ==== lbString demo ==== //
	std::string str = "RACE car";
	std::vector<std::string> words = lbString::split(str, " ");

	for (unsigned i = 0; i < words.size(); i++)
	{
		lbString::toLower(words[i]);
		WARN(words[i]);
		lbString::toUpper(words[i]);
		WARN(words[i]);
	}

	// ==== lbCSV demo ==== //
	// fakelist.csv doens't exist, will thrown an error
	TABLE fakeList = lbCSV::read("fakelist.csv");
	TABLE list = lbCSV::read("example/list.csv");
	// Check out the log, or set the log level to show LOG if you want to see the read results

	// Throwing an error that will end the program
	FATAL("Bye bye");

	INFO("You should not be able to see this info message!");

	// Normal program ending
	lbLog::endLog();

	return 0;

}

#endif // _LB_EXAMPLE
