#ifndef SEVEXCEPTION_H
#define SEVEXCEPTION_H

#include <exception>
#include <string>
#include <QString>

#include "severity.h"

class SevException : public std::exception {
public:
  SevException(const Severity severity, const std::string& message)
    : severity_(severity), message_(message) { }

  SevException(const Severity severity, const QString& message)
    : severity_(severity), message_(message.toStdString()) { }

  Severity severity() const noexcept {
    return severity_;
  }

  const char* what() const noexcept override {
    return message_.c_str();
  }

private:
    Severity     severity_;
    std::string  message_;
};

#endif
