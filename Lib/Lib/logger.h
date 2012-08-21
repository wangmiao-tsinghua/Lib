#ifndef LOGGER_H_
#define LOGGER_H_

#include <Windows.h>
#include <string>


class Logger
{
	static const int kBuffer_len = 1024;
public:
	Logger();
	~Logger();

	static void init(	const std::string &file_name,
		bool append = true, 
		bool bPrefix = true	);

	//inline: set and get _prefix 
	inline static void set_prefix( bool bPrefix) { _bPrefix = bPrefix ;}
	inline static bool prefix()  { return _bPrefix; }

	//log information
	static void log(const std::string &msg);
	static void log(const char *msg);

	static void logLine(const char *format, ...);
	static void logLine(WORD attribs, const char * format, ...);

	static void logError(const char* format, ...);
	
	static void logWarning(const char* format, ...);

	static void logConsole(const char* format, ...);

	static void clear();

	static void demo();


private:
	static HANDLE _hConsole;
	static std::string _file_name;
	static bool _bPrefix;

	//Just for avoiding debug warning when writeConsole is called
	static DWORD gConsoleWritenLen; 
	static char gLogBufferA [kBuffer_len];

	// Some time information about current line of log
	static void logPrefix(FILE* file);
};

























#endif
