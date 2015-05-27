#include "severity.h"

template<>
const std::map<Severity, std::string> EnumToString<Severity>::map_{{Severity::DEBUG,   "DEB"},
                                                                   {Severity::WARNING, "WAR"},
                                                                   {Severity::ERROR,   "ERR"},
                                                                   {Severity::INFO,    "INF"},
                                                                   {Severity::NONE,    "NON"}};
