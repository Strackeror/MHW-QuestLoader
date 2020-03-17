#include "loader.h"
#include "dll.h"

#include <fstream>
#include <ctime>

using namespace loader;

LogLevel loader::MinLogLevel = INFO;

bool configLoaded = false;

bool logcmd = false;
bool logfile = false;

void logToFile(const char* stamp, const char* msg)
{

	if (!logfile) return;

	std::ofstream o("loader.log", std::ios::ate);

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
		SetConsoleTitle("Stracker's Loader");
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

static std::map<std::string, LogLevel> logLevels = {
	{"DEBUG", DEBUG},
	{"INFO", INFO },
	{"WARNING", WARN},
	{"ERROR", ERR}
};

void _log(int l, const char* s) 
{
	if (!configLoaded)
	{
		configLoaded = true;
		loader::MinLogLevel = logLevels.at(ConfigFile.value<std::string>("logLevel", "ERROR"));
		logcmd = ConfigFile.value<bool>("logcmd", false);
		logfile = ConfigFile.value<bool>("logfile", false);
	}
	if (l < MinLogLevel)
		return;

	time_t mytime = time(NULL);
	tm mytm;
	localtime_s(&mytm, &mytime);
	char stamp[128] = { 0 };
	strftime(stamp, sizeof(stamp), "%H:%M:%S", &mytm);

	logToFile(stamp, s);
	logToConsole(l, stamp, s);
}

LOG::~LOG() {
	stream << std::endl;
	stream.flush();
	_log((int)logLevel, stream.str().c_str());
}
