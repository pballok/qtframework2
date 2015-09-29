#include <QSettings>

#include "sevexception.h"

#include "preferences.h"

void Preferences::load() {
    QSettings pref_file(file_name_, QSettings::IniFormat);
    if(pref_file.status() != QSettings::NoError) {
        throw SevException(Severity::WARNING, QString("Failed to read from preferences file: %1").arg(file_name_));
    }

    readLoggerPreferences(pref_file);
    readCustomPreferences(pref_file);
}

void Preferences::save() const {
    QSettings pref_file(file_name_, QSettings::IniFormat);
    if(pref_file.status() != QSettings::NoError) {
        throw SevException(Severity::WARNING, QString("Failed to write to preferences file: %1").arg(file_name_));
    }

    writeLoggerPreferences(pref_file);
    writeCustomPreferences(pref_file);
}

void Preferences::readLoggerPreferences(const QSettings& pref_file) {
    console_level_ = SeverityString::fromString(pref_file.value("LogLevels/Console").toString().toStdString(), Severity::DEBUG);
    file_level_    = SeverityString::fromString(pref_file.value("LogLevels/File").toString().toStdString(), Severity::DEBUG);
}

void Preferences::writeLoggerPreferences(QSettings& pref_file) const {
    pref_file.setValue("LogLevels/Console", SeverityString::toString(console_level_).c_str());
    pref_file.setValue("LogLevels/File", SeverityString::toString(file_level_).c_str());
}
