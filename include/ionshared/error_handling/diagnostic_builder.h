#pragma once

#include <string>
#include "diagnostic.h"

namespace ionshared {
    /**
     * Helper class to easily build and bootstrap diagnostics.
     */
    class DiagnosticBuilder : public std::enable_shared_from_this<DiagnosticBuilder> {
    private:
        Ptr<DiagnosticStack> diagnosticStack;

        std::optional<Diagnostic> diagnosticBuffer;

        void assertDiagnosticBufferSet() const;

    public:
        [[nodiscard]] static std::string createTrace(Diagnostic diagnostic) noexcept;

        [[nodiscard]] static std::string findDiagnosticTypeText(DiagnosticType type);

        explicit DiagnosticBuilder(Ptr<DiagnosticStack> diagnosticStack);

        DiagnosticBuilder();

        [[nodiscard]] Ptr<DiagnosticStack> getDiagnosticStack() const noexcept;

        void setDiagnosticStack(Ptr<DiagnosticStack> diagnosticStack) noexcept;

        [[nodiscard]] std::optional<Diagnostic> getDiagnosticBuffer() const noexcept;

        void setDiagnosticBuffer(std::optional<Diagnostic> diagnosticBuffer) noexcept;

        void clearDiagnosticBuffer() noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> begin(Diagnostic diagnostic) noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> begin(
            DiagnosticType type,
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> beginInfo(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> beginWarning(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder>beginError(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> beginFatal(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        [[nodiscard]] bool internalAssert(bool condition) noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> setCode(std::optional<uint32_t> code);

        [[nodiscard]] Ptr<DiagnosticBuilder> setExample(std::optional<std::string> example);

        bool finish();

        bool bootstrap(
            Diagnostic diagnostic,
            std::optional<SourceLocation> sourceLocation = std::nullopt
        );
    };
}
