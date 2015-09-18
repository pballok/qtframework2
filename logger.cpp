#include "logger.h"

std::unique_ptr<ILogger> the_logger{nullptr};

LogMessage::~LogMessage() {
    logger_->writeMessage(severity_, stream_.str());
}
