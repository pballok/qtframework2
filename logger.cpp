#include "logger.h"

std::unique_ptr<ILogger> the_logger{nullptr};

LogMessage::LogMessage(Severity sev, ILogger* const logger) :
    logger_{logger},
    severity_{sev} {
        std::time_t t  = std::time(nullptr);
        std::tm*    tm = std::localtime(&t);
        stream_ << std::put_time(tm, "%e-%b-%Y %H:%M:%S ") << SeverityString::toString(sev) << " ";
}

LogMessage::~LogMessage() {
    logger_->sendMessage(severity_, stream_.str());
}

LoggerDecorator::LoggerDecorator(std::unique_ptr<ILogger> b, Severity sev) : ILogger(sev),
                                                                             base_{std::move(b)},
                                                                             receiver_thread_(&LoggerDecorator::receiveMessage, this) {
    max_reporting_level_ = std::max(sev, base_->max_reporting_level());
}

LoggerDecorator::~LoggerDecorator() {
}

void LoggerDecorator::receiveMessage() {
    while(true) {
        std::unique_lock<std::mutex> ml(queue_mutex_);
        message_arrived_.wait(ml);
    }
}

void FileLogger::outputMessage(const LogMessage &message) {
    if(sev <= reporting_level_ && !file_stream_.fail()) file_stream_ << message << std::endl;
}

void ConsoleLogger::outputMessage(const LogMessage &message) {

}
