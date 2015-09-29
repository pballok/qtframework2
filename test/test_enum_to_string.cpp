#include <gtest/gtest.h>
#include <sstream>

#include "severity.h"

TEST(EnumToString, ToString) {
    EXPECT_EQ("DEB", SeverityString::toString(Severity::DEBUG));
    EXPECT_EQ("WAR", SeverityString::toString(Severity::WARNING));
    EXPECT_EQ("ERR", SeverityString::toString(Severity::ERROR));
    EXPECT_EQ("INF", SeverityString::toString(Severity::INFO));
    EXPECT_EQ("NON", SeverityString::toString(Severity::NONE));
}

TEST(EnumToString, FromString) {
    EXPECT_EQ(Severity::DEBUG,   SeverityString::fromString("DEB"));
    EXPECT_EQ(Severity::WARNING, SeverityString::fromString("WAR"));
    EXPECT_EQ(Severity::ERROR,   SeverityString::fromString("ERR"));
    EXPECT_EQ(Severity::INFO,    SeverityString::fromString("INF"));
    EXPECT_EQ(Severity::NONE,    SeverityString::fromString("NON"));
    EXPECT_EQ(Severity::INFO,    SeverityString::fromString("WHATEVER", Severity::INFO));
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
