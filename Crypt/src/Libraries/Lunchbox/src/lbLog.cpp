//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/lunchbox
//
//	@Project:	Lunchbox Toolset
//
//	@Last Updated:	2015-10-02 10:26:38
//	@Created:		2015-07-14 21:26:08
//
//===============================================//

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

#include "../include/lbLog.h"

// Pre decalre static vars
int lbLog::_logLevel = lbLog::none;
int lbLog::_fileLogLevel = lbLog::all;
int lbLog::_quitLevel = lbLog::fatal;
std::ofstream lbLog::_logFile;

// Create the file. *For now*, only one file at a time.
void lbLog::_createLog(std::string path, std::string fileName) {
	if (!_logFile.is_open()) {
		_logFile.open((path+fileName).c_str());
		INFO(" === STARTED LOG ===" );
	} else {
		WARN("Already an active log file. Close the active one before beginning another!");
	}
}

// Add next line to file
void lbLog::_writeToFile(std::string newLine) {
	if (_logFile.is_open()) {
		_logFile << newLine + "\n";
		_logFile.flush();
	}
}

// Gets date and time to be used for file names
std::string lbLog::_getDateTime(bool justTime) {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);

	if (justTime) {
		// Only return the time. Used for prefixing logs
		strftime(buf, sizeof(buf), "%X", &tstruct);
	} else {
		strftime(buf, sizeof(buf), "%Y.%m.%d-%X", &tstruct);
	}

	return buf;
}

// Start logging to file, with standard name and root location
void lbLog::startLog() {
	_createLog("",(_getDateTime(false)+".log").c_str());
}	

// Start logging to file, with custom fileName and custom location, with the option of adding timestamp
void lbLog::startLog(std::string path, std::string fileName, bool addTimeStamp) {
	std::string fullFileName;
	fullFileName = fileName;
	if (addTimeStamp)
	{
		if (fileName != "")
		{
			fullFileName += "-";
		}
		fullFileName += _getDateTime(false);
	}
	fullFileName += ".log";
	_createLog(path,(fullFileName).c_str());
}	

// Close the file, to stop corruption and loose ends
void lbLog::endLog() {
	if (_logFile.is_open()) {
		INFO(" === ENDED LOG ===");
		_logFile.close();
	}
}

// Set the logging level viewable from within the program. Required
void lbLog::setLogLevel(int newLevel) {
	_logLevel = newLevel;
}

// Set the loggling level to go to the text file
void lbLog::setFileLogLevel(int newLevel) {
	_fileLogLevel = newLevel;
}

// Set the threshold for the program to quit
void lbLog::setQuitLevel(int newLevel) {
	_quitLevel = newLevel;
}

void lbLog::quickSet(int newLogLevel, int newFileLogLevel, int newQuitLevel) {
	setLogLevel(newLogLevel);
	setFileLogLevel(newFileLogLevel);
	setQuitLevel(newQuitLevel);
}

// Print out if logging level is met. Should always be called from a macro
void lbLog::out(const char* fileTrace, int lineTrace, std::string levelTag, int sentLevel, std::string msg) {

	std::string toLog = "["+_getDateTime(true)+"]["+levelTag+"]:"+fileTrace+":"+std::to_string(lineTrace)+": "+msg;

	// Quit
	if (sentLevel <= _quitLevel)
	{
		std::cout << toLog << std::endl;
		_writeToFile(toLog);

		endLog();
		std::exit(1);
	}

	// Outputting to screen
	if (sentLevel <= _logLevel)
	{
		std::cout << toLog << std::endl;
	}

	// Outputting to file
	if (sentLevel <= _fileLogLevel)
	{
		_writeToFile(toLog);
	}
}
