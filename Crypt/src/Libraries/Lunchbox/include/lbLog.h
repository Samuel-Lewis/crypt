//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/lunchbox
//
//	@Project:	Lunchbox Toolset
//
//	@Last Updated:	2015-11-12 16:33:30
//	@Created:		2015-07-14 21:26:08
//
//===============================================//

#ifndef _LB_LOG_H
#define _LB_LOG_H

#include <fstream>
#include <string>
#include <sstream>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// Different error levels to be called through the rest of the program
#define FATAL(msg) { std::stringstream lbLog_sstream_input; lbLog_sstream_input << msg; lbLog::out(__FILENAME__, __LINE__, "FATAL", lbLog::fatal, lbLog_sstream_input.str().c_str()); }
#define ERROR(msg) { std::stringstream lbLog_sstream_input; lbLog_sstream_input << msg; lbLog::out(__FILENAME__, __LINE__, "ERROR", lbLog::error, lbLog_sstream_input.str().c_str()); }
#define WARN(msg) { std::stringstream lbLog_sstream_input; lbLog_sstream_input << msg; lbLog::out(__FILENAME__, __LINE__, "WARNING", lbLog::warn, lbLog_sstream_input.str().c_str()); }
#define INFO(msg) { std::stringstream lbLog_sstream_input; lbLog_sstream_input << msg; lbLog::out(__FILENAME__, __LINE__, "INFO", lbLog::info, lbLog_sstream_input.str().c_str()); }
#define LOG(msg) { std::stringstream lbLog_sstream_input; lbLog_sstream_input << msg; lbLog::out(__FILENAME__, __LINE__, "LOG", lbLog::log, lbLog_sstream_input.str().c_str()); }
#define MARK() { lbLog::out(__FILENAME__, __LINE__, "MARK", lbLog::mark, ""); }

class lbLog {
public:
	enum sevLevels {
		none = 0,
		fatal,
		error,
		warn,
		info,
		log,
		mark,
		all
	};

	// Level setters
	static void setLogLevel(int);
	static void setFileLogLevel(int);
	static void setQuitLevel(int);
	static void quickSet(int, int, int);

	// Should only really be called from the macro.
	static void out(const char*, int, std::string, int, std::string);

	// Starts putting logs in to a txt for the duration of the exectuion, or until endLog() is called
	static void startLog();
	static void startLog(std::string, std::string, bool);
	static void endLog();

private:
	// Stop the initialization of a lbLog
	lbLog();
	~lbLog();

	static int _logLevel;
	static int _fileLogLevel;
	static int _quitLevel;
	static std::ofstream _logFile;

	static void _writeToFile(std::string);
	static void _createLog(std::string, std::string);
	static std::string _getDateTime(bool);
};

#endif //_LB_LOG_H
