#pragma once

#include <ionshared/diagnostics/diagnostic.h>
#include <ionshared/diagnostics/diagnostic_builder.h>

namespace ionshared {
    struct PassContext {
        const Ptr<Set<Diagnostic>> diagnosticsSet;

        const Ptr<DiagnosticBuilder> diagnosticBuilder;
    };
}
