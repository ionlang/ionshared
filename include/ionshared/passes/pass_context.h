#pragma once

#include <ionshared/error_handling/diagnostic.h>
#include <ionshared/error_handling/diagnostic_builder.h>

namespace ionshared {
    class PassContext {
    private:
        ionshared::Ptr<ionshared::DiagnosticStack> diagnosticStack;

        ionshared::Ptr<ionshared::DiagnosticBuilder> diagnosticBuilder;

    public:
        explicit PassContext(
            const ionshared::Ptr<ionshared::DiagnosticStack> &diagnosticStack
        );

        [[nodiscard]] ionshared::Ptr<ionshared::DiagnosticStack> getDiagnosticStack() const noexcept;

        [[nodiscard]] ionshared::Ptr<ionshared::DiagnosticBuilder> getDiagnosticBuilder() const noexcept;
    };
}
