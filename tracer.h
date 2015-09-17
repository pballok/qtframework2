#ifndef TRACER_H
#define TRACER_H

#include "logger.h"

struct TracerIndent{
    static int indent;
    TracerIndent() { indent += indent_step; }
    ~TracerIndent() { indent -= indent_step; }
private:
    static const int indent_step;
};

#define TRACE_IN \
    TracerIndent tracer_indent; \
    LOG(DEBUG) << std::string(TracerIndent::indent, ' ') << __PRETTY_FUNCTION__ << " > "

#define TRACE_OUT \
    LOG(DEBUG)  << std::string(TracerIndent::indent, ' ') << __PRETTY_FUNCTION__ << " < "

#endif
