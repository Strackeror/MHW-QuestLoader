#pragma once
#include <windows.h>
#include <sdkddkver.h>

#include <sstream>
#include <vector>

#ifdef DINPUT8MHW_EXPORTS
#define DllExport   __declspec( dllexport )
#else
#define DllExport   __declspec( dllimport )
#endif

#pragma warning( disable: 4251 )

namespace loader {
	enum LogLevel {
		DEBUG = 0,
		INFO = 1,
		WARN = 2,
		ERR = 3
	};

	DllExport extern const char* GameVersion;
	DllExport extern LogLevel MinLogLevel;

	class DllExport LOG
	{
	private:
		std::stringstream stream;
		LogLevel logLevel;
		LOG(const LOG& o) = delete;
		LOG& operator=(const LOG& o) = delete;
	public:
		LOG(LogLevel level) :logLevel(level) {}
		~LOG();

		template<class T>
		LOG& operator<<(const T& x) {
			if (logLevel >= MinLogLevel)
				stream << x;
			return *this;
		}
	};
}
