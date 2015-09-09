#ifndef LOGGER_H
#define LOGGER_H

#include <memory>

#include "severity.h"

// Logger using the Decorator Pattern
// https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator

class ILogger {
public:
    virtual ~ILogger() { }

    virtual void writeMessage() = 0;
};

class Logger : public ILogger {
public:
    void writeMessage() override { }
};

class LoggerDecorator : public ILogger {
public:
    LoggerDecorator(std::unique_ptr<ILogger> b, Severity sev) : reporting_level_{sev} { b_ = std::move(b); }
protected:
    std::unique_ptr<ILogger> b_;
    Severity                 reporting_level_;
};

class FileLogger : public LoggerDecorator {
public:
    FileLogger(std::unique_ptr<ILogger> b, Severity sev, const std::string& file_name)
        : LoggerDecorator(std::move(b), sev),
          file_name_{file_name} { }

    void writeMessage() override { }

protected:
    std::string file_name_;
};

#endif
