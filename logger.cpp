#include "logger.h"

std::unique_ptr<ILogger> the_logger = std::make_unique<Logger>(Severity::NONE);
