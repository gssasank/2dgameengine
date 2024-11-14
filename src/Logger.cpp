#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "Logger.h"

std::vector<LogEntry> Logger::messages;

std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%d-%m-%Y %H:%M:%S");

    return ss.str();
}

void Logger::Log(const std::string& message){
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG | " + getCurrentDateTime() + " - " + message;
    std::cout << "\033[32m" << logEntry.message << "\033[0m" << std::endl;

    messages.push_back(logEntry);
}

void Logger::Err(const std::string& message){
    LogEntry logEntry;
    logEntry.type = LOG_ERROR;
    logEntry.message = "ERR | " + getCurrentDateTime() + " - " + message;
    std::cout << "\033[31m" << logEntry.message << "\033[0m" << std::endl;

    messages.push_back(logEntry);
}