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

	template<typename... Args>
	inline void NeoLog(LogLevel level, const char* fmt, Args&&... args) {
		if (!m_Initialized) return;

		std::lock_guard<std::mutex> lock(m_Mutex);

		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);

		std::tm tm;
		localtime_s(&tm, &time);

		std::string message = std::vformat(fmt, std::make_format_args(args...));
		std::string formatted = std::format("[{:02}:{:02}:{:02}] [{}] {}", tm.tm_hour, tm.tm_min, tm.tm_sec, LevelToString(level), message);
		PrintToConsole(level, formatted);

		if (m_Log_File.is_open()) {
			m_Log_File << formatted << std::endl;
		}
	}
};

#define NEOLOG_INFO(fmt, ...)     Logging::NeoLog(LogLevel::Info, fmt, __VA_ARGS__)
#define NEOLOG_WARN(fmt, ...)     Logging::NeoLog(LogLevel::Warning, fmt, __VA_ARGS__)
#define NEOLOG_ERROR(fmt, ...)    Logging::NeoLog(LogLevel::Error, fmt, __VA_ARGS__)
#define NEOLOG_DEBUG(fmt, ...)    Logging::NeoLog(LogLevel::Debug, fmt, __VA_ARGS__)