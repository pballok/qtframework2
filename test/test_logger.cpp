#include <gtest/gtest.h>

#include "logger.h"

TEST(Logger, ConsoleLogger) {
    the_logger = std::make_unique<ConsoleLogger>(std::make_unique<Logger>(), Severity::WARNING);

    LOG(DEBUG) << "Test DEBUG message" << " Using only " << 1 << " ConsoleLogger";
}
