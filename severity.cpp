#include "severity.h"

template<>
const std::map<Severity, std::string> SeverityString::map_{{Severity::NONE,    "NON"},
                                                           {Severity::INFO,    "INF"},
                                                           {Severity::ERROR,   "ERR"},
                                                           {Severity::WARNING, "WAR"},
                                                           {Severity::DEBUG,   "DEB"}};
