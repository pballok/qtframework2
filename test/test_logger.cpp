#include <gtest/gtest.h>

#include "logger.h"

TEST(Logger, ConsoleLogger) {
    the_logger = std::make_shared<FileLogger>(std::make_unique<FileLogger>(std::make_unique<Logger>(), Severity::WARNING, "test1.log"), Severity::INFO, "test2.log");

    LOG(ERROR) << "Test DEBUG message" << " Using only " << 1 << " ConsoleLogger";
}
