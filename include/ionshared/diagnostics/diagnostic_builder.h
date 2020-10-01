#pragma once

#include <string>
#include <ionshared/misc/util.h>
#include <ionshared/container/vector.h>
#include "diagnostic.h"

namespace ionshared {
    /**
     * Helper class to easily build and bootstrap diagnostics.
     */
    class DiagnosticBuilder : public std::enable_shared_from_this<DiagnosticBuilder> {
    private:
        std::optional<Diagnostic> diagnosticBuffer;

        void assertDiagnosticBufferSet() const;

        void setDiagnosticBuffer(std::optional<Diagnostic> diagnosticBuffer) noexcept;

    public:
        const Ptr<Vector<Diagnostic>> diagnostics;

        explicit DiagnosticBuilder(
            Ptr<Vector<Diagnostic>> diagnostics =
                std::make_shared<Vector<Diagnostic>>()
        );

        [[nodiscard]] std::optional<Diagnostic> getDiagnosticBuffer() const noexcept;

        void clearDiagnosticBuffer() noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> begin(Diagnostic diagnostic) noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> begin(
            DiagnosticKind type,
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

        [[nodiscard]] Ptr<DiagnosticBuilder> setMessage(std::string message);

        [[nodiscard]] Ptr<DiagnosticBuilder> setSourceLocation(
            std::optional<SourceLocation> location
        );

        [[nodiscard]] Ptr<DiagnosticBuilder> setCode(std::optional<uint32_t> code);

        [[nodiscard]] Ptr<DiagnosticBuilder> setAdditionalInformation(
            std::optional<std::string> additionalInformation
        );

        [[nodiscard]] Ptr<DiagnosticBuilder> setExample(
            std::optional<std::string> example
        );

        void finish();

        /**
         * Will attempt to format the currently buffered diagnostic's
         * message with the provided arguments. If the formatting fails,
         * the message will not be changed.
         */
        template<typename ...Args>
        [[nodiscard]] Ptr<DiagnosticBuilder> formatMessage(Args &&...args) {
            this->assertDiagnosticBufferSet();

            std::optional<std::string> formattedMessage = util::formatStringA(
                this->diagnosticBuffer->message,
                util::convertString(std::forward<Args>(args))...
            );

            if (formattedMessage.has_value()) {
                this->diagnosticBuffer->message = *formattedMessage;
            }

            return this->shared_from_this();
        }

        [[nodiscard]] Ptr<DiagnosticBuilder> bootstrap(
            Diagnostic diagnostic,
            std::optional<SourceLocation> sourceLocation = std::nullopt
        );
    };
}
