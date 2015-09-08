#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

#include "preferences.h"

TEST(Preferences, AppName) {
    Preferences pref("TestApp", "1.2.3");
    EXPECT_EQ("TestApp", pref.app_name());
}

TEST(Preferences, Version) {
    Preferences pref("TestApp", "1.2.3");
    EXPECT_EQ("1.2.3", pref.version());
}

TEST(Preferences, ReadFromFile) {
    Preferences pref("TestAppIn", "1,2.3");
    pref.load();
    EXPECT_EQ(Severity::DEBUG, pref.console_level());
    EXPECT_EQ(Severity::ERROR, pref.file_level());
}

TEST(Preferences, WriteToFile) {
    Preferences pref("TestAppOut", "1,2.3");
    pref.set_console_level(Severity::INFO);
    pref.set_file_level(Severity::ERROR);
    pref.save();

    std::ifstream     generated_file("TestAppOut.ini");
    std::stringstream generated_stream;
    generated_stream << generated_file.rdbuf();

    std::ifstream     expected_file("TestAppExpected.ini");
    std::stringstream expected_stream;
    expected_stream << expected_file.rdbuf();

    EXPECT_EQ(expected_stream.str(), generated_stream.str());
}
