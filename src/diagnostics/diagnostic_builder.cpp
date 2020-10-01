#include <ionshared/misc/util.h>
#include <ionshared/diagnostics/diagnostic_builder.h>

namespace ionshared {
    void DiagnosticBuilder::assertDiagnosticBufferSet() const {
        if (!this->diagnosticBuffer.has_value()) {
            throw std::runtime_error("Expected diagnostic buffer to be set");
        }
    }

    DiagnosticBuilder::DiagnosticBuilder(Ptr<Vector<Diagnostic>> diagnostics) :
        diagnostics(diagnostics),
        diagnosticBuffer(std::nullopt) {
        //
    }

    std::optional<Diagnostic> DiagnosticBuilder::getDiagnosticBuffer() const noexcept {
        return this->diagnosticBuffer;
    }

    void DiagnosticBuilder::setDiagnosticBuffer(std::optional<Diagnostic> diagnosticBuffer) noexcept {
        this->diagnosticBuffer = diagnosticBuffer;
    }

    void DiagnosticBuilder::clearDiagnosticBuffer() noexcept {
        this->diagnosticBuffer = std::nullopt;
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::begin(Diagnostic diagnostic) noexcept {
        // TODO: Overwrites the SourceLocation field on the current buffer.
        this->setDiagnosticBuffer(diagnostic);

        return this->shared_from_this();
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::begin(
        DiagnosticKind type,
        std::string message,
        std::optional<SourceLocation> location
    ) noexcept {
        return this->begin(Diagnostic{
            type,
            message,
            location
        });
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginInfo(
        std::string message,
        std::optional<SourceLocation> location
    ) noexcept {
        return this->begin(DiagnosticKind::Info, message, location);
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginWarning(
        std::string message,
        std::optional<SourceLocation> location
    ) noexcept {
        return this->begin(DiagnosticKind::Warning, message, location);
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginError(
        std::string message,
        std::optional<SourceLocation> location
    ) noexcept {
        return this->begin(DiagnosticKind::Error, message, location);
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginFatal(
        std::string message,
        std::optional<SourceLocation> location
    ) noexcept {
        return this->begin(DiagnosticKind::Fatal, message, location);
    }

    bool DiagnosticBuilder::internalAssert(bool condition) noexcept {
        if (!condition) {
            this->begin(DiagnosticKind::InternalError, "Internal assertion failed")
                ->finish();
        }

        return condition;
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::setMessage(std::string message) {
        this->assertDiagnosticBufferSet();
        this->diagnosticBuffer->message = message;

        return this->shared_from_this();
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::setSourceLocation(std::optional<SourceLocation> location) {
        this->assertDiagnosticBufferSet();
        this->diagnosticBuffer->sourceLocation = location;

        return this->shared_from_this();
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::setCode(std::optional<uint32_t> code) {
        this->assertDiagnosticBufferSet();
        this->diagnosticBuffer->code = code;

        return this->shared_from_this();
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::setAdditionalInformation(
        std::optional<std::string> additionalInformation
    ) {
        this->assertDiagnosticBufferSet();
        this->diagnosticBuffer->additionalInformation = additionalInformation;

        return this->shared_from_this();
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::setExample(std::optional<std::string> example) {
        this->assertDiagnosticBufferSet();
        this->diagnosticBuffer->example = example;

        return this->shared_from_this();
    }

    void DiagnosticBuilder::finish() {
        // TODO: Should it clear buffer after finish?

        this->assertDiagnosticBufferSet();
        this->diagnostics->add(*this->diagnosticBuffer);
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::bootstrap(
        Diagnostic diagnostic,
        std::optional<SourceLocation> sourceLocation
    ) {
        Diagnostic newDiagnostic = Diagnostic{
            diagnostic.kind,
            diagnostic.message,
            sourceLocation,
            diagnostic.code,
            diagnostic.example
        };

        return this->begin(newDiagnostic);
    }
}
