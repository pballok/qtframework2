#include "tracer.h"

const int Tracer::indent_step_ = 2;
int Tracer::indent_ = -Tracer::indent_step_;

Tracer::Tracer(const char* func_name) : function_name_{func_name},
                                        logged_message_{false} { }

Tracer::~Tracer() {
    if(logged_message_) {
        LogMessage tracer_msg = the_logger->log(Severity::DEBUG);
        tracer_msg << "TRACE " << std::string(indent_, ' ') << function_name_ << " <" << results_.str();
        indent_ -= indent_step_;
    }
}
