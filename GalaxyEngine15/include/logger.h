#pragma once
#include "..\stdafx.h"
#include <ctime>
#include <stdarg.h>

#define MsgLoger logger::Instance()
#define LogError logger::Instance().logError
#define LogMessage logger::Instance().logMessage

class logger
{
public:
	static logger& Instance()
	{
		static logger singleton;
		return singleton;
	}

	enum ErrorLogMode
	{
		ERROR_LOG_MODE_FILE,
		ERROR_LOG_MODE_CONSOLE,
		ERROR_LOG_MODE_BOTH
	};

	static void setLogMode(ErrorLogMode mode);

	static void logError(const char* message, ...);
	static void logMessage(const char* message, ...);

private:
	logger() {};                           // Private constructor
	logger(const logger&);                 // Prevent copy-construction
	logger& operator=(const logger&);      // Prevent assignment

	static std::string getFormattedTime();
	static void commitLogMessage(std::ostream &os, const char* msg);
	static void commitErrorLogEntry(std::ostream &os, const char* msg);
};

