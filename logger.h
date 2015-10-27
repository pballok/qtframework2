#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <sstream>
#include <utility>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "severity.h"

// Logger using the Decorator Pattern
// https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator


class ILogger;

class LogMessage final {
public:
    LogMessage(Severity sev, ILogger* const logger) : logger_{logger},
                                                      time_stamp_{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())},
                                                      severity_{sev},
                                                      message_{} { }
    LogMessage(const LogMessage&) = default;
    LogMessage(LogMessage&&)      = default;
    ~LogMessage();

    template <typename T>
    LogMessage& operator<<(const T& t) { std::ostringstream ss; ss << t; message_ += ss.str(); return *this; }

    std::string timeStamp() const { std::ostringstream ss; ss << std::put_time(std::localtime(&time_stamp_), "%e-%b-%Y %H:%M:%S"); return ss.str(); }
    Severity    severity()  const { return severity_; }
    std::string message()   const { return message_; }

private:
    ILogger* const  logger_;
    std::time_t     time_stamp_;
    const Severity  severity_;
    std::string     message_;
};



class QueuedMessage final {
public:
    QueuedMessage(const LogMessage& msg) : time_stamp_{msg.timeStamp()},
                                           severity_{msg.severity()},
                                           message_{msg.message()} { }

    Severity    severity()  const { return severity_; }
    std::string message()   const { return message_; }

    friend std::ostream& operator <<(std::ostream&, const QueuedMessage& message);

private:
    std::string     time_stamp_;
    const Severity  severity_;
    std::string     message_;
};



class ILogger {
public:
    explicit ILogger(Severity sev) : reporting_level_{sev}, max_reporting_level_{sev} { }
    virtual ~ILogger() { }

    LogMessage   log(Severity sev)           { return LogMessage(sev, this); }
    Severity     max_reporting_level() const { return max_reporting_level_; }
    virtual void sendMessage(const LogMessage&) = 0;

protected:
    Severity                reporting_level_;
    Severity                max_reporting_level_;

    virtual void receiveMessage() = 0;
};



class Logger : public ILogger {
public:
    explicit Logger(Severity sev = Severity::DEBUG) : ILogger(sev) { }
    void sendMessage(const LogMessage&) override { }

protected:
    void receiveMessage() override { }
};



class LoggerDecorator : public ILogger {
public:
    LoggerDecorator(std::unique_ptr<ILogger> b, Severity sev);

protected:
    std::unique_ptr<ILogger>      base_;
    std::thread                   receiver_thread_;
    std::queue<QueuedMessage>     message_queue_;
    std::mutex                    queue_mutex_;
    std::condition_variable       message_arrived_;

    void         sendMessage(const LogMessage& message) override;
    void         receiveMessage() override;
    virtual void outputMessage(const QueuedMessage& message) = 0;
    void         endQueue();
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

    ~FileLogger() { endQueue(); }

protected:
    std::ofstream file_stream_;

    void outputMessage(const QueuedMessage& message) override;
};



class ConsoleLogger : public LoggerDecorator {
public:
    ConsoleLogger(std::unique_ptr<ILogger> b, Severity sev)
        : LoggerDecorator(std::move(b), sev) { }

    ~ConsoleLogger() { endQueue(); }

protected:
    void outputMessage(const QueuedMessage& message) override;
};



extern std::unique_ptr<ILogger> the_logger;

#define LOG(LEVEL) \
    if(static_cast<int>(Severity::LEVEL) > static_cast<int>(the_logger->max_reporting_level())) ; \
    else the_logger->log(Severity::LEVEL)

#endif
