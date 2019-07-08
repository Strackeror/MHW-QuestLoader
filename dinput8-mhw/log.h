#pragma once
#include <windows.h>
#include <sdkddkver.h>

#include <iostream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>


enum LogLevel {
	INFO = 0,
	WARN = 1,
	ERR = 2
};
extern LogLevel min_log_level;

struct LOG {
protected:
	std::stringstream s_;
	LogLevel l_;
	LOG(const LOG& o) = delete;
	LOG& operator=(const LOG& o) = delete;
public:
	LOG(LogLevel l) :l_(l) {}
	~LOG();
	template<class T>
	LOG& operator<<(const T& x) {
		s_ << x;
		return *this;
	}
	LOG& operator<<(const std::wstring& s) {
		return *this << std::string(s.begin(), s.end());
	}
	LOG& operator<<(const wchar_t* s) {
		return *this << std::wstring(s);
	}
};

template<typename T>
LOG& operator<<(LOG& o, const std::vector<T>& v) {
	o << "[";
	for (size_t i = 0; i < v.size(); i++)
		o << v[i] << (i + 1 < v.size() ? ", " : "]");
	return o;
}

#define ASSERT(x) {if (!(x)) LOG(ERR) << __FILE__ << ":" << __LINE__ << "    Assertion failed! " << #x; }

static char* getLogFilename() {
	static char tmp[256] = "intercept.log";
	GetEnvironmentVariableA("LOGFILE", tmp, sizeof(tmp));
	return tmp;
}
static char* log_filename = getLogFilename();

#ifdef _DEBUG
LogLevel min_log_level = INFO;
#else
LogLevel min_log_level = WARN;
#endif // DEBUG


__declspec(dllexport) void _log(int l, const char* s) {

	if (l >= min_log_level) {
		static std::ofstream o(log_filename);
		time_t mytime = time(NULL);
		tm mytm;
		localtime_s(&mytm, &mytime);
		char stamp[128] = { 0 };
		strftime(stamp, sizeof(stamp), "%H:%M:%S", &mytm);
		o << "[ " << stamp << " ] " << s;
		o.flush();
		{
			static HANDLE console = 0;
			if (!console) {
				AllocConsole();
				SetConsoleTitle("Intercept Log");
				console = GetStdHandle(STD_OUTPUT_HANDLE);
			}
			SetConsoleTextAttribute(console, FOREGROUND_GREEN);
			WriteConsole(console, "[ ", 2, nullptr, 0);
			WriteConsole(console, stamp, (DWORD)strlen(stamp), nullptr, 0);
			WriteConsole(console, " ] ", 3, nullptr, 0);

			if (l == INFO)
				SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			if (l == WARN)
				SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			if (l == ERR)
				SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
			WriteConsole(console, s, (DWORD)strlen(s), nullptr, 0);
			SetConsoleTextAttribute(console, 0);
		}
	}
}

LOG::~LOG() {
	s_ << std::endl;
	s_.flush();
	_log((int)l_, s_.str().c_str());
}
