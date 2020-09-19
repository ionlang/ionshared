#include <ionshared/passes/pass_context.h>

namespace ionshared {
    PassContext::PassContext(const Ptr<DiagnosticStack> &diagnosticStack) :
        diagnosticStack(diagnosticStack),
        diagnosticBuilder(std::make_shared<DiagnosticBuilder>(diagnosticStack)) {
        //
    }

    PassContext::PassContext() :
        PassContext(std::make_shared<DiagnosticStack>()) {
        //
    }

    Ptr<DiagnosticStack> PassContext::getDiagnosticStack() const noexcept {
        return this->diagnosticStack;
    }

    Ptr<DiagnosticBuilder> PassContext::getDiagnosticBuilder() const noexcept {
        return this->diagnosticBuilder;
    }
}
