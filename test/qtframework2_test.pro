TEMPLATE     = app
CONFIG      += c++14
QT          -= gui
LIBS        += -lgtest -lgtest_main
DESTDIR      = $$PWD
INCLUDEPATH += ..

SOURCES     += ../logger.cpp \
               ../preferences.cpp \
               ../severity.cpp \
               ../tracer.cpp \
               test_enum_to_string.cpp \
               test_logger.cpp \
               test_preferences.cpp \
               test_tracer.cpp

HEADERS     += ../enum_to_string.h \
               ../iapplicationpreferences.h \
               ../iloggerpreferences.h \
               ../logger.h \
               ../preferences.h \
               ../severity.h \
               ../tracer.h
