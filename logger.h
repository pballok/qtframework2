#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <sstream>
#include <utility>
#include <string>
#include <fstream>

#include "severity.h"

// Logger using the Decorator Pattern
// https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator


class ILogger;

class LogMessage final {
public:
    LogMessage(Severity sev, ILogger* logger) :
        logger_{logger},
        severity_{sev} { stream_ << EnumToString<Severity>::toString(sev) << " "; }

    LogMessage(LogMessage&& other) {
        logger_   = other.logger_;
        severity_ = other.severity_;
        stream_   = std::move(other.stream_);

        other.logger_ = nullptr;
    }
    ~LogMessage();

    template <typename T>
    LogMessage& operator<<(const T& t) { stream_ << t; return *this; }

private:
    ILogger*            logger_;
    Severity            severity_{Severity::NONE};
    std::ostringstream  stream_;
};



class ILogger {
public:
    explicit ILogger(Severity sev) : reporting_level_{sev}, max_reporting_level_{Severity::NONE} { }
    virtual ~ILogger() { }

    LogMessage   log(Severity sev)           { return LogMessage(sev, this); }
    Severity     reporting_level() const     { return reporting_level_; }
    Severity     max_reporting_level() const { return max_reporting_level_; }
    virtual void writeMessage(Severity sev, const std::string&) = 0;

protected:
    Severity reporting_level_;
    Severity max_reporting_level_;
};



class Logger : public ILogger {
public:
    explicit Logger(Severity sev = Severity::DEBUG) : ILogger(sev) { }
    void writeMessage(Severity, const std::string&) override { }
};



class LoggerDecorator : public ILogger {
public:
    LoggerDecorator(std::unique_ptr<ILogger> b, Severity sev) : ILogger(sev) { base_ = std::move(b); max_reporting_level_ = std::max(sev, base_->max_reporting_level()); }
protected:
    std::unique_ptr<ILogger> base_;
};



class FileLogger : public LoggerDecorator {
public:
    FileLogger(std::unique_ptr<ILogger> b, Severity sev, const std::string& file_name)
        : LoggerDecorator(std::move(b), sev),
          file_stream_{file_name, std::ofstream::out | std::ofstream::app} {
            if(file_stream_.fail()) {
                reporting_level_ = Severity::NONE;
                max_reporting_level_ = base_->max_reporting_level();
            }

        }

    void writeMessage(Severity sev, const std::string& message) override {
        base_->writeMessage(sev, message);
        if(sev <= reporting_level_ && !file_stream_.fail()) file_stream_ << message << std::endl;
    }

protected:
    std::ofstream file_stream_;
};



class ConsoleLogger : public LoggerDecorator {
public:
    ConsoleLogger(std::unique_ptr<ILogger> b, Severity sev)
        : LoggerDecorator(std::move(b), sev) { }

    void writeMessage(Severity sev, const std::string& message) override {
        base_->writeMessage(sev, message);
        if(sev <= reporting_level_) std::cerr << message << std::endl;
    }
};



extern std::shared_ptr<ILogger> the_logger;

#define LOG(LEVEL) \
    if(static_cast<int>(Severity::LEVEL) > static_cast<int>(the_logger->max_reporting_level())) ; \
    else the_logger->log(Severity::LEVEL)

#endif
