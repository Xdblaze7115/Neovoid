#pragma once
#include <mutex>
#include <fstream>
#include <chrono>
#include <string>

enum class LogLevel {
	Debug,
	Info,
	Warning,
	Error
};

namespace Logging {
	extern std::mutex m_Mutex;
	extern std::ofstream m_Log_File;
	extern bool m_Initialized;

	void Initialize();
	void Shutdown();
	const char* LevelToString(LogLevel level);
	void PrintToConsole(LogLevel level, std::string msg);
	void NeoLog(LogLevel level, const char* fmt, ...);
};

#define NEOLOG_INFO(fmt, ...)     Logging::NeoLog(LogLevel::Info, fmt, __VA_ARGS__)
#define NEOLOG_WARN(fmt, ...)     Logging::NeoLog(LogLevel::Warning, fmt, __VA_ARGS__)
#define NEOLOG_ERROR(fmt, ...)    Logging::NeoLog(LogLevel::Error, fmt, __VA_ARGS__)
#define NEOLOG_DEBUG(fmt, ...)    Logging::NeoLog(LogLevel::Debug, fmt, __VA_ARGS__)