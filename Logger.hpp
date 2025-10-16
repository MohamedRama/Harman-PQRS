#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace Logger {

    enum class Level { INFO, WARN, ERROR, DEBUG };

    inline std::string timestamp() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
        localtime_r(&time, &tm);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    inline void log(Level level, const std::string& msg) {
        const char* levelStr = nullptr;
        switch(level) {
            case Level::INFO:  levelStr = "INFO"; break;
            case Level::WARN:  levelStr = "WARN"; break;
            case Level::ERROR: levelStr = "ERROR"; break;
            case Level::DEBUG: levelStr = "DEBUG"; break;
        }
        std::cout << "[" << timestamp() << "] [" << levelStr << "] " << msg << std::endl;
    }

    #define LOG_INFO(msg)  Logger::log(Logger::Level::INFO,  msg)
    #define LOG_WARN(msg)  Logger::log(Logger::Level::WARN,  msg)
    #define LOG_ERROR(msg) Logger::log(Logger::Level::ERROR, msg)
    #define LOG_DEBUG(msg) Logger::log(Logger::Level::DEBUG, msg)
}
