#ifndef LOGGER_H
#define LOGGER_H

#include <memory>

// Logger using the Decorator Pattern
// https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator

class ILogger {
public:
    virtual ~Logger() { }

    virtual void writeMessage() = 0;
};

class Logger : public ILogger {
public:
    void writeMessage() override { }
};

class LoggerDecorator : public ILogger {
public:
    LoggerDecorator(std::unique_ptr<ILogger> b) { b = std::move(b); }
private:
    std::unique_ptr<ILogger> b_;
};

class ConsoleLogger : public LoggerDecorator {
public:
    ConsoleLogger(std::unique_ptr<ILogger> c) : LoggerDecorator(c) { }

    void writeMessage() override { }
};

#endif
