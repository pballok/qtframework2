#include <gtest/gtest.h>

#include "tracer.h"

void testHelper3() {
    TRACE_IN << "Helper 3 started";
}


int testHelper2(int i, int j) {
    TRACE_IN << i << ", " << j;

    testHelper3();

    TRACE_OUT << i + j;

    return i + j;
}


void testHelper1() {
    TRACE_IN;

    testHelper2(42, 38);

    TRACE_OUT;
}



TEST(Tracer, Tracer) {
    std::remove("test1.log");
    the_logger = std::make_unique<FileLogger>(std::make_unique<Logger>(), Severity::DEBUG, "test1.log");

    testHelper1();

    the_logger.reset();

    std::ifstream     generated_log_1("test1.log");
    std::stringstream generated_stream_1;
    generated_stream_1 << generated_log_1.rdbuf();
    std::string       log_contents_1 = generated_stream_1.str();

    EXPECT_NE(std::string::npos, log_contents_1.find("DEB void testHelper1() >"));
    EXPECT_NE(std::string::npos, log_contents_1.find("DEB   int testHelper2(int, int) > 42, 38"));
    EXPECT_NE(std::string::npos, log_contents_1.find("DEB     void testHelper3() > Helper 3 started"));
    EXPECT_NE(std::string::npos, log_contents_1.find("DEB   int testHelper2(int, int) < 80"));
    EXPECT_NE(std::string::npos, log_contents_1.find("DEB void testHelper1() <"));
}
