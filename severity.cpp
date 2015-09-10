#include "severity.h"

template<>
const std::map<Severity, std::string> EnumToString<Severity>::map_{{Severity::INFO,    "INF"},
                                                                   {Severity::ERROR,   "ERR"},
                                                                   {Severity::WARNING, "WAR"},
                                                                   {Severity::DEBUG,   "DEB"},
                                                                   {Severity::NONE,    "NON"}};
