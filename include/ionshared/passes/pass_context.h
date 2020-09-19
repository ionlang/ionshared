#pragma once

#include <ionshared/error_handling/diagnostic.h>
#include <ionshared/error_handling/diagnostic_builder.h>

namespace ionshared {
    class PassContext {
    private:
        Ptr<DiagnosticStack> diagnosticStack;

        Ptr<DiagnosticBuilder> diagnosticBuilder;

    public:
        explicit PassContext(
            const Ptr<DiagnosticStack> &diagnosticStack
        );

        PassContext();

        [[nodiscard]] Ptr<DiagnosticStack> getDiagnosticStack() const noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> getDiagnosticBuilder() const noexcept;
    };
}
