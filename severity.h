#ifndef SEVERITY_H
#define SEVERITY_H

#include <iostream>

#include "enum_to_string.h"

enum class Severity { NONE, INFO, ERROR, WARNING, DEBUG };

using SeverityString = EnumToString<Severity>;

inline std::ostream& operator<<(std::ostream& s, const Severity sev) { return s << SeverityString::toString(sev); }
inline std::istream& operator>>(std::istream& s, Severity& sev) { std::string s_value; s >> s_value; sev = SeverityString::fromString(s_value); return s; }

#endif // SEVERITY_H
