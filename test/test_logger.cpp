#include <gtest/gtest.h>

#include "logger.h"

TEST(Logger, AppName) {
    std::unique_ptr<FileLogger> logger = std::make_unique<FileLogger>(std::make_unique<Logger>(), Severity::WARNING, "test.log");

//    logger->log(Severity::DEBUG) << "Test DEBUG message";
}
