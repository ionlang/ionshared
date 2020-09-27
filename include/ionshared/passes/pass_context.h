#pragma once

#include <ionshared/diagnostics/diagnostic.h>
#include <ionshared/diagnostics/diagnostic_builder.h>

namespace ionshared {
    struct PassContext {
        const Ptr<Vector<Diagnostic>> diagnostics;

        const Ptr<DiagnosticBuilder> diagnosticBuilder;

        explicit PassContext(
            Ptr<Vector<Diagnostic>> diagnostics =
                std::make_shared<Vector<Diagnostic>>()
        );
    };
}
