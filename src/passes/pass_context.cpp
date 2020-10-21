#include <ionshared/passes/pass_context.h>

namespace ionshared {
    PassContext::PassContext(
        std::shared_ptr<Vector<Diagnostic>> diagnostics
    ) noexcept :
        diagnostics(diagnostics),
        diagnosticBuilder(std::make_shared<DiagnosticBuilder>(diagnostics)) {
        //
    }
}
