#include "logger.h"
#include <sys/timeb.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//Just for avoiding debug warning when writeConsole is called
DWORD Logger::gConsoleWritenLen; 
char Logger::gLogBufferA[Logger::kBuffer_len];

HANDLE Logger::_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::string Logger::_file_name;
bool Logger::_bPrefix = true;

void Logger::init(	const std::string &file_name,
					bool append /*= true */, 
					bool bPrefix /*= true */ )
{
	_file_name = file_name;

	if(!append)
	{
		FILE *file = fopen(_file_name.c_str() , "w");
		if(file != NULL)
			fclose(file);
	}

	_bPrefix = prefix;

	return ;
}

void Logger::logPrefix( FILE* file )
{
	if( prefix() == false)
		return ;

	timeb tb;
	ftime(&tb);

	char gDataTime[64];

	strftime(	gDataTime, sizeof(gDataTime), "%y/%m/%d %H:%M:%S",
				localtime(&tb.time));

	fprintf(file, "[%s:%03d] ", gDataTime, tb.millitm);
	
	return ;
}

void Logger::log( const char *msg )
{
	FILE *file = fopen(_file_name.c_str(), "a+");

	if(file != NULL)
	{
		 logPrefix(file);
		 fprintf(file, "%s", msg);
		 fclose(file);
	}
	if(_hConsole)
		printf("%s",msg);
	return ;
}

void Logger::log( const std::string &msg )
{
	log(msg.c_str());
	return ;
}

void Logger::logLine( const char *format, ... )
{
	char buf[1 << 16];
	va_list args;
	va_start( args, format );
	vsnprintf(buf, 1<<16, format, args );
	log(buf);
}

void Logger::logLine( WORD attribs, const char * format, ... )
{
	if (_hConsole) 
		SetConsoleTextAttribute(_hConsole, attribs);

	char buf[1 << 16];
	va_list args;
	va_start( args, format );
	vsnprintf(buf, 1<<16, format, args );
	log(buf);

	if (_hConsole)
	{
		SetConsoleTextAttribute(	_hConsole,
			FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE	);
	}
	return ;
}

void Logger::logError( const char* fmt, ... )
{
	char buf[1 << 16];
	strcpy(buf, "Error: ");
	va_list args;
	va_start( args, fmt );
	vsnprintf(buf + 7, 1<<16, fmt, args );
	logLine(FOREGROUND_RED | FOREGROUND_INTENSITY, buf);

	exit(1);
}

void Logger::logWarning( const char* fmt, ... )
{
	char buf[1 << 16];
	strcpy(buf, "Warning: ");
	va_list args;
	va_start( args, fmt );
	vsnprintf(buf + 9, 1<<16, fmt, args );
	logLine(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, buf);
}

void Logger::logConsole( const char* fmt, ... )
{
	if (_hConsole == NULL)
		return;

	char buf[1 << 16];
	va_list args;
	va_start( args, fmt );
	vsnprintf(buf, 1<<16, fmt, args );
	printf(buf);
}

void Logger::clear()
{
	FILE* file = fopen(_file_name.c_str(), "w");
	fclose(file);
}

void Logger::demo()
{
	printf("%s:%d\n", __FILE__, __LINE__);
	
	Logger::init("logger.log");

	Logger::log("Test 1 2 3 4 5 6  7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31\n");
	Logger::log("Test 1 2 3 4 5 6  7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31\n");

	Logger::logLine("\t \t %s\n","Logger by Miao Wang");

	Logger::logLine(	FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY, 
						"%d  %s\n",
						1,
						"Test 1 2 3 4 5 6  7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31");
	
	Logger::logWarning("%s %d %s\n",  __FILE__, __LINE__, __FILE__);

	//Logger::logError("%s %d %s\n",  __FILE__, __LINE__, __FILE__);

	Logger::set_prefix(false);

	Logger::log("prefix false\n");

	Logger::clear();
	
	return ;
}
