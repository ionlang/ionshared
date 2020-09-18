#include <ionshared/passes/pass_context.h>

namespace ionshared {
    PassContext::PassContext(const ionshared::Ptr<ionshared::DiagnosticStack> &diagnosticStack) :
        diagnosticStack(diagnosticStack),
        diagnosticBuilder(std::make_shared<DiagnosticBuilder>(diagnosticStack)) {
        //
    }

    ionshared::Ptr<ionshared::DiagnosticStack> PassContext::getDiagnosticStack() const noexcept {
        return this->diagnosticStack;
    }

    ionshared::Ptr<ionshared::DiagnosticBuilder> PassContext::getDiagnosticBuilder() const noexcept {
        return this->diagnosticBuilder;
    }
}
