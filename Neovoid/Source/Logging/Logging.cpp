#include <iostream>
#include <cstdarg>
#include <filesystem>
#include "Logging.hpp"

namespace Logging {
	std::mutex m_Mutex;
	std::ofstream m_Log_File;
	bool m_Initialized = false;

	void Initialize() {
		std::filesystem::path logs_directory = std::filesystem::current_path() / "Logs";
		std::filesystem::create_directories(logs_directory);

		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);

		std::tm tm;
		localtime_s(&tm, &time);

		std::ostringstream oss;
		oss << "Engine_"
			<< std::put_time(&tm, "%Y-%m-%d-%H-%M-%S")
			<< ".log";
		std::filesystem::path log_file_path = logs_directory / oss.str();

		m_Log_File.open(log_file_path, std::ios::out);
		if (!m_Log_File.is_open()) {
			throw std::runtime_error("Failed to open log file -> " + log_file_path.string());
		}
		m_Initialized = true;
	}

	void Shutdown() {
		m_Log_File.close();
		m_Initialized = false;
	}

	const char* LevelToString(LogLevel level) {
		switch (level) {
		case LogLevel::Debug:
			return "DEBUG";
		case LogLevel::Info:
			return "INFO";
		case LogLevel::Warning:
			return "WARN";
		case LogLevel::Error:
			return "ERROR";
		}
		return "UNKNOWN";
	}

	void PrintToConsole(LogLevel level, std::string msg) {
		switch (level) {
		case LogLevel::Debug:
			std::cout << "\033[37m"; break;
		case LogLevel::Info:
			std::cout << "\033[36m"; break;
		case LogLevel::Warning:
			std::cout << "\033[33m"; break;
		case LogLevel::Error:
			std::cout << "\033[31m"; break;
		}
		std::cout << msg << "\033[0m" << std::endl;
	}

	void NeoLog(LogLevel level, const char* fmt, ...) {
		if (!m_Initialized) return;

		std::lock_guard<std::mutex> lock(m_Mutex);

		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);

		std::tm tm;
		localtime_s(&tm, &time);

		char buffer[2048];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buffer, sizeof(buffer), fmt, args);
		va_end(args);

		std::ostringstream output;
		output << "[" << std::put_time(&tm, "%H:%M:%S") << "] [" << LevelToString(level) << "] " << buffer;
		std::string formatted = output.str();
		PrintToConsole(level, formatted);

		if (m_Log_File.is_open()) {
			m_Log_File << formatted << std::endl;
		}
	}
}