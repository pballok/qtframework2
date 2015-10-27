#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <set>
#include <string>

#include "logger.h"

TEST(Logger, FileLogger) {
    std::remove("test1.log");
    std::remove("test2.log");

    the_logger = std::make_unique<FileLogger>(std::make_unique<FileLogger>(std::make_unique<Logger>(), Severity::WARNING, "test1.log"), Severity::INFO, "test2.log");

    LOG(ERROR) << "Test ERROR message " << 1;
    LOG(DEBUG) << "Test DEBUG message " << 2;
    LOG(INFO)  << "Test INFO message "  << 3;
    LOG(ERROR) << "Test ERROR message " << 4;

    the_logger.reset();

    std::ifstream     generated_log_1("test1.log");
    std::stringstream generated_stream_1;
    generated_stream_1 << generated_log_1.rdbuf();
    std::string       log_contents_1 = generated_stream_1.str();

    std::ifstream     generated_log_2("test2.log");
    std::stringstream generated_stream_2;
    generated_stream_2 << generated_log_2.rdbuf();
    std::string       log_contents_2 = generated_stream_2.str();

    EXPECT_NE(std::string::npos, log_contents_1.find("Test ERROR message 1"));
    EXPECT_EQ(std::string::npos, log_contents_2.find("Test ERROR message 1"));

    EXPECT_EQ(std::string::npos, log_contents_1.find("Test DEBUG message 2"));
    EXPECT_EQ(std::string::npos, log_contents_2.find("Test DEBUG message 2"));

    EXPECT_NE(std::string::npos, log_contents_1.find("Test INFO message 3"));
    EXPECT_NE(std::string::npos, log_contents_2.find("Test INFO message 3"));

    EXPECT_NE(std::string::npos, log_contents_1.find("Test ERROR message 4"));
    EXPECT_EQ(std::string::npos, log_contents_2.find("Test ERROR message 4"));
}

TEST(Logger, MultiThread) {
    std::remove("test1.log");
    std::remove("test2.log");

    constexpr int log_count = 100;

    the_logger = std::make_unique<FileLogger>(std::make_unique<Logger>(), Severity::WARNING, "test1.log");

    std::thread t1{[](){ for(int i = 0; i < log_count; ++i) { LOG(ERROR) << "Message " << i << " from Thread 1"; }}};
    std::thread t2{[](){ for(int i = 0; i < log_count; ++i) { LOG(ERROR) << "Message " << i << " from Thread 2"; }}};
    std::thread t3{[](){ for(int i = 0; i < log_count; ++i) { LOG(ERROR) << "Message " << i << " from Thread 3"; }}};

    t1.join();
    t2.join();
    t3.join();

    the_logger.reset();

    std::ifstream              generated_log("test1.log");
    std::multiset<std::string> log_lines;
    std::string                line;
    constexpr int              message_pos = 25;
    while(std::getline(generated_log, line)) log_lines.emplace(line.substr(message_pos));

    EXPECT_EQ(log_count * 3, log_lines.size());

    std::stringstream message;
    for(int i = 0; i < log_count; ++i) {
        message.str("");
        message << "Message " << i << " from Thread 1";
        EXPECT_NE(log_lines.end(), log_lines.find(message.str())) << "Missing \"" << message.str() << "\"";

        message.str("");
        message << "Message " << i << " from Thread 2";
        EXPECT_NE(log_lines.end(), log_lines.find(message.str())) << "Missing \"" << message.str() << "\"";

        message.str("");
        message << "Message " << i << " from Thread 3";
        EXPECT_NE(log_lines.end(), log_lines.find(message.str())) << "Missing \"" << message.str() << "\"";
    }
}
