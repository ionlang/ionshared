#include <ionshared/passes/pass_context.h>

namespace ionshared {
    PassContext::PassContext(Ptr<Vector<Diagnostic>> diagnostics) :
        diagnostics(diagnostics),
        diagnosticBuilder(std::make_shared<DiagnosticBuilder>(diagnostics)) {
        //
    }
}
