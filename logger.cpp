#include "logger.h"

std::unique_ptr<ILogger> the_logger{nullptr};

inline LogMessage::~LogMessage() {
    logger_->writeMessage(severity_, stream_.str());
}

void Logger::receiveMessage() override {
    while(true) {
        std::unique_lock<std::mutex> lock{queue_mutex};
    }
}
