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
    console_level_ = EnumToString<Severity>::fromString(pref_file.value("LogLevels/Console").toString().toStdString());
    if(console_level_ == Severity::UNDEFINED) console_level_ = Severity::DEBUG;

    file_level_ = EnumToString<Severity>::fromString(pref_file.value("LogLevels/File").toString().toStdString());
    if(file_level_ == Severity::UNDEFINED) file_level_ = Severity::DEBUG;
}

void Preferences::writeLoggerPreferences(QSettings& pref_file) const {
    pref_file.setValue("LogLevels/Console", EnumToString<Severity>::toString(console_level_).c_str());
    pref_file.setValue("LogLevels/File", EnumToString<Severity>::toString(file_level_).c_str());
}
