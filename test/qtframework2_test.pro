TEMPLATE     = app
CONFIG      += c++14
QT          -= gui
LIBS        += -lgtest -lgtest_main
DESTDIR      = $$PWD
INCLUDEPATH += ..

SOURCES     += ../preferences.cpp \
               ../severity.cpp \
               test_enum_to_string.cpp \
               test_logger.cpp \
               test_preferences.cpp

HEADERS     += ../enum_to_string.h \
               ../iapplicationpreferences.h \
               ../iloggerpreferences.h \
               ../logger.h \
               ../preferences.h \
               ../severity.h
