#include "log.h"
#include "dll.h"

#include <fstream>

bool configLoaded = false;

LogLevel min_log_level = INFO;
bool logcmd = false;
bool logfile = false;

void logToFile(const char* stamp, const char* msg)
{
	static std::ofstream o;

	if (!logfile) return;

	if (!o.is_open())
		o = std::ofstream("dinput-loader.log");

	o << "[ " << stamp << " ] " << msg;
	o.flush();
}

void logToConsole(int l, const char* stamp, const char* msg)
{
	static HANDLE console = 0;
	if (!logcmd) return;

	if (!console )
	{
		AllocConsole();
		SetConsoleTitle("Intercept Log");
		console = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	SetConsoleTextAttribute(console, FOREGROUND_GREEN);
	WriteConsole(console, "[ ", 2, nullptr, 0);
	WriteConsole(console, stamp, (DWORD)strlen(stamp), nullptr, 0);
	WriteConsole(console, " ] ", 3, nullptr, 0);

	if (l == INFO || l == DEBUG)
		SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	if (l == WARN)
		SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	if (l == ERR)
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
	WriteConsole(console, msg, (DWORD)strlen(msg), nullptr, 0);
	SetConsoleTextAttribute(console, 0);

}

void _log(int l, const char* s) 
{
	if (!configLoaded)
	{
		configLoaded = true;
		logcmd = ConfigFile.value<bool>("logcmd", false);
		logfile = ConfigFile.value<bool>("logfile", false);
	}

	if (l >= min_log_level) {
		time_t mytime = time(NULL);
		tm mytm;
		localtime_s(&mytm, &mytime);
		char stamp[128] = { 0 };
		strftime(stamp, sizeof(stamp), "%H:%M:%S", &mytm);

		logToFile(stamp, s);
		logToConsole(l, stamp, s);
	}
}

LOG::~LOG() {
	s_ << std::endl;
	s_.flush();
	_log((int)l_, s_.str().c_str());
}
