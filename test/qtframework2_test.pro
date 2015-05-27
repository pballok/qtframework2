TEMPLATE     = app
CONFIG      += c++11
QT          -= gui
LIBS        += -lgtest -lgtest_main
INCLUDEPATH += ..

SOURCES     += ../severity.cpp \
               test_enum_to_string.cpp

HEADERS     += ../enum_to_string.h \
               ../severity.h
