#include "..\include\logger.h"
#include "..\include\video_includes.h"

logger::ErrorLogMode mLogMode;
std::string logFileName = "log.txt";

void logger::setLogMode(ErrorLogMode mode)
{
	mLogMode = mode;
}

void logger::logMessage(const char* message, ...)
{
	va_list argptr;
	FILE* file; 
	
	errno_t ec = fopen_s(&file, logFileName.c_str(), "a");

	if (!file) {
		fprintf (
			stderr,
			"ERROR: could not open %s file for appending\n",
			logFileName.c_str()
			);
	}

	fprintf(file, getFormattedTime().c_str());

	va_start (argptr, message);
	vfprintf (file, message, argptr);
	vprintf(message, argptr);
	va_end (argptr);

	fclose (file);
}

void logger::logError(const char* message, ...)
{
	va_list argptr;

	FILE* file;

	errno_t ec = fopen_s(&file, logFileName.c_str(), "a");

	if (!file) {
		fprintf (
			stderr,
			"ERROR: could not open %s file for appending\n",
			logFileName.c_str()
			);
	}

	fprintf(file, getFormattedTime().c_str());

	va_start (argptr, message);
	vfprintf (file, message, argptr);
	va_end (argptr);

	va_start (argptr, message);
	vfprintf (stderr, message, argptr);
	va_end (argptr);

	fclose (file);
}

std::string logger::getFormattedTime()
{
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time (&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer,80,"%m/%d/%Y %I:%M:%S",&timeinfo);
	std::string str(buffer);
	str += " - ";
	return str;
}

void logger::commitErrorLogEntry(std::ostream &os, const char* msg)
{
	os << getFormattedTime().c_str() << " - ** " << msg << std::endl;
}

void logger::commitLogMessage(std::ostream &os, const char* msg)
{
	os << getFormattedTime().c_str() << " - " << msg << std::endl;
}
