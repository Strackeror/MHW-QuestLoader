#pragma once
#include <windows.h>
#include <sdkddkver.h>

#include <sstream>
#include <filesystem>
#include <vector>

#ifdef DINPUT8MHW_EXPORTS
#define DllExport   __declspec( dllexport )
#else
#define DllExport   __declspec( dllimport )
#endif



enum LogLevel {
	DEBUG = 0,
	INFO = 1,
	WARN = 2,
	ERR = 3
};
extern LogLevel min_log_level;

#pragma warning( disable: 4251 )

class DllExport LOG 
{
private:
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
};

template<typename T>
LOG& operator<<(LOG& o, const std::vector<T>& v) {
	o << "[";
	for (size_t i = 0; i < v.size(); i++)
		o << v[i] << (i + 1 < v.size() ? ", " : "]");
	return o;
}

#define ASSERT(x) {if (!(x)) LOG(ERR) << __FILE__ << ":" << __LINE__ << "    Assertion failed! " << #x; }

