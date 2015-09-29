#ifndef I_LOGGER_PREFERENCES_H
#define I_LOGGER_PREFERENCES_H

#include "severity.h"

class QSettings;

class ILoggerPreferences {
public:
    virtual ~ILoggerPreferences() { }

    virtual Severity console_level() const = 0;
    virtual void set_console_level(Severity console_level) = 0;

    virtual Severity file_level() const = 0;
    virtual void set_file_level(Severity file_level) = 0;

protected:
    virtual void readLoggerPreferences(const QSettings& pref_file) = 0;
    virtual void writeLoggerPreferences(QSettings& pref_file) const = 0;
};

#endif
