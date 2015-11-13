#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>

#include "iapplicationpreferences.h"
#include "iloggerpreferences.h"

namespace {
    constexpr unsigned int QTFRAMEWORK_VERSION_MAJOR = 2;
    constexpr unsigned int QTFRAMEWORK_VERSION_MINOR = 5;
    constexpr unsigned int QTFRAMEWORK_VERSION_PATCH = 0;
}

class Preferences : public IApplicationPreferences,
                    public ILoggerPreferences {
public:
    Preferences(const QString& app_name, const QString& version)
        : app_name_{app_name},
          file_name_{app_name + ".ini"},
          version_{version},
          console_level_{Severity::DEBUG},
          file_level_{Severity::DEBUG} { }

    QString  app_name() const override final { return app_name_; }
    QString  version() const override final { return version_; }

    Severity console_level() const override final { return console_level_; }
    void     set_console_level(Severity console_level) { console_level_ = console_level; }

    Severity file_level() const override final { return file_level_; }
    virtual void set_file_level(Severity file_level) { file_level_ = file_level; }

    void load();
    void save() const;

protected:
    void readLoggerPreferences(const QSettings& pref_file) override final;
    void writeLoggerPreferences(QSettings& pref_file) const override final;

    virtual void readCustomPreferences(const QSettings&) { }
    virtual void writeCustomPreferences(QSettings&) const { }

protected:
    QString  app_name_;
    QString  file_name_;
    QString  version_;
    Severity console_level_;
    Severity file_level_;
};

#endif
