#ifndef TRACER_H
#define TRACER_H

#include "logger.h"

class Tracer {
public:
    explicit Tracer(const char* func_name);
    ~Tracer();

    template<class... Params>
    void writeEntry(Params... params) {
        LogMessage tracer_msg = the_logger->log(Severity::DEBUG);

        indent_ += indent_step_;
        tracer_msg << "TRACE " << std::string(indent_, ' ') << function_name_ << " >";
        traceParams(tracer_msg, params...);

        logged_message_ = true;
    }

    template<class T, class... Tail>
    void addResult(T param, Tail... tail) {
        results_ << " \"" << param << "\"";
        addResult(tail...);
    }

    static void addResult() { }

private:
    static int         indent_;
    static const int   indent_step_;

    const char*        function_name_;
    bool               logged_message_;
    std::ostringstream results_;

    template<class T, class... Tail>
    static void traceParams(LogMessage& message, T param, Tail... tail) {
        traceParams(message << " \"" << param << "\"", tail...);
    }

    static void traceParams(LogMessage&) { }
};

#define TRACE_ME(...) \
    Tracer trace_me(__PRETTY_FUNCTION__); \
    if(static_cast<int>(Severity::DEBUG) <= static_cast<int>(the_logger->max_reporting_level())) \
        trace_me.writeEntry(__VA_ARGS__);

#define TRACE_RESULT(...) \
    if(static_cast<int>(Severity::DEBUG) <= static_cast<int>(the_logger->max_reporting_level())) \
        trace_me.addResult(__VA_ARGS__);

#endif
