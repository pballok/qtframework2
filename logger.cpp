#include <chrono>

#include "logger.h"



std::unique_ptr<ILogger> the_logger{nullptr};



LogMessage::~LogMessage() {
    logger_->sendMessage(*this);
}



std::ostream& operator <<(std::ostream& os, const QueuedMessage& message) {
    os << message.time_stamp_ << " " << SeverityString::toString(message.severity_) << " " << message.message_ << std::endl;
    return os;
}



LoggerDecorator::LoggerDecorator(std::unique_ptr<ILogger> b, Severity sev) : ILogger(sev),
                                                                             base_{std::move(b)},
                                                                             receiver_thread_(&LoggerDecorator::receiveMessage, this) {
    max_reporting_level_ = std::max(sev, base_->max_reporting_level());
}



void LoggerDecorator::endQueue() {
    {
        LogMessage end_message(Severity::NONE, this);
        end_message << "END";
    }

    receiver_thread_.join();
}



void LoggerDecorator::sendMessage(const LogMessage& message) {
    if(static_cast<int>(message.severity()) <= static_cast<int>(reporting_level_)) {
        std::unique_lock<std::mutex> ml(queue_mutex_);
        message_queue_.emplace(message);
        ml.unlock();

        message_arrived_.notify_one();
    }

    base_->sendMessage(message);
}



void LoggerDecorator::receiveMessage() {
    while(true) {
        std::unique_lock<std::mutex> ml(queue_mutex_);

        message_arrived_.wait(ml, [this]{ return !message_queue_.empty(); });

        QueuedMessage message = message_queue_.front();

        message_queue_.pop();
        ml.unlock();

        if(message.severity() == Severity::NONE && message.message() == "END") break;

        outputMessage(message);
    }
}



void FileLogger::outputMessage(const QueuedMessage &message) {
    if(!file_stream_.fail()) file_stream_ << message;
}



void ConsoleLogger::outputMessage(const QueuedMessage &message) {
    std::cerr << message;
}
