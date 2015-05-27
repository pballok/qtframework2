#include <sstream>

#include <gtest/gtest.h>

#include "severity.h"

TEST(EnumToString, ToString) {
    EXPECT_EQ("DEB",                                     EnumToString<Severity>::toString(Severity::DEBUG));
    EXPECT_EQ("WAR",                                     EnumToString<Severity>::toString(Severity::WARNING));
    EXPECT_EQ("ERR",                                     EnumToString<Severity>::toString(Severity::ERROR));
    EXPECT_EQ("INF",                                     EnumToString<Severity>::toString(Severity::INFO));
    EXPECT_EQ("NON",                                     EnumToString<Severity>::toString(Severity::NONE));
    EXPECT_EQ("EnumToString::toString(): Unknown value", EnumToString<Severity>::toString(Severity::UNDEFINED));
}

TEST(EnumToString, FromString) {
    EXPECT_EQ(Severity::DEBUG,     EnumToString<Severity>::fromString("DEB"));
    EXPECT_EQ(Severity::WARNING,   EnumToString<Severity>::fromString("WAR"));
    EXPECT_EQ(Severity::ERROR,     EnumToString<Severity>::fromString("ERR"));
    EXPECT_EQ(Severity::INFO,      EnumToString<Severity>::fromString("INF"));
    EXPECT_EQ(Severity::NONE,      EnumToString<Severity>::fromString("NON"));
    EXPECT_EQ(Severity::UNDEFINED, EnumToString<Severity>::fromString("WHATEVER"));
}

TEST(EnumToString, OutStream) {
    std::ostringstream os;
    os << Severity::DEBUG << " " << Severity::INFO;
    EXPECT_EQ("DEB INF", os.str());
}

TEST(EnumToString, InStream) {
    std::istringstream is("NON ERR");
    Severity s1, s2;
    is >> s1 >> s2;
    EXPECT_EQ(Severity::NONE,  s1);
    EXPECT_EQ(Severity::ERROR, s2);
}
