#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <sstream>

#include "severity.h"

// Logger using the Decorator Pattern
// https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator

namespace {
    class LogMessage final {
    public:
        LogMessage(Severity sev) : severity_{sev} { }
        LogMessage(LogMessage&& other) {
            severity_ = other.severity_;
            stream_   = std::move(other.stream_);
        }
        ~LogMessage() {
            std::cout << EnumToString<Severity>::toString(severity_) << " " << stream_.str() << std::endl;
        }

        template <typename T>
        LogMessage& operator<<(const T& t) { stream_ << t; return *this; }

    private:
        Severity           severity_{Severity::NONE};
        std::ostringstream stream_;
    };
}

class ILogger {
public:
    explicit ILogger(Severity sev) : reporting_level_{sev} { }
    virtual ~ILogger() { }

    LogMessage   log(Severity sev)       { return LogMessage(sev); }
    Severity     reporting_level() const { return reporting_level_; }
    virtual void writeMessage() = 0;

protected:
    Severity reporting_level_;
};

class Logger : public ILogger {
public:
    explicit Logger(Severity sev = Severity::DEBUG) : ILogger(sev) { }
    void writeMessage() override { }
};

class LoggerDecorator : public ILogger {
public:
    LoggerDecorator(std::unique_ptr<ILogger> b, Severity sev) : ILogger(sev) { b_ = std::move(b); }
protected:
    std::unique_ptr<ILogger> b_;
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

class ConsoleLogger : public LoggerDecorator {
public:
    ConsoleLogger(std::unique_ptr<ILogger> b, Severity sev)
        : LoggerDecorator(std::move(b), sev) { }

    void writeMessage() override { }
};

extern std::unique_ptr<ILogger> the_logger;

#define LOG(LEVEL) \
    if(static_cast<int>(Severity::LEVEL) > static_cast<int>(the_logger->reporting_level())) ; \
    else the_logger->log(Severity::LEVEL)

#endif
