#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "logger.h"

TEST(Logger, FileLogger) {
    std::remove("test1.log");
    std::remove("test2.log");

    the_logger = std::make_unique<FileLogger>(std::make_unique<FileLogger>(std::make_unique<Logger>(), Severity::WARNING, "test1.log"), Severity::INFO, "test2.log");

    LOG(ERROR) << "Test ERROR message " << 1;
    LOG(DEBUG) << "Test DEBUG message " << 2;
    LOG(INFO)  << "Test INFO message "  << 3;
    LOG(ERROR) << "Test ERROR message " << 4;

    std::ifstream     generated_log_1("test1.log");
    std::stringstream generated_stream_1;
    generated_stream_1 << generated_log_1.rdbuf();
    std::string       log_contents_1 = generated_stream_1.str();

    std::ifstream     generated_log_2("test2.log");
    std::stringstream generated_stream_2;
    generated_stream_2 << generated_log_2.rdbuf();
    std::string       log_contents_2 = generated_stream_2.str();

    EXPECT_NE(log_contents_1.find("Test ERROR message 1"), std::string::npos);
    EXPECT_EQ(log_contents_2.find("Test ERROR message 1"), std::string::npos);

    EXPECT_EQ(log_contents_1.find("Test DEBUG message 2"), std::string::npos);
    EXPECT_EQ(log_contents_2.find("Test DEBUG message 2"), std::string::npos);

    EXPECT_NE(log_contents_1.find("Test INFO message 3"),  std::string::npos);
    EXPECT_NE(log_contents_2.find("Test INFO message 3"),  std::string::npos);

    EXPECT_NE(log_contents_1.find("Test ERROR message 4"), std::string::npos);
    EXPECT_EQ(log_contents_2.find("Test ERROR message 4"), std::string::npos);
}
