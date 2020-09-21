#include <ionshared/misc/util.h>
#include <ionshared/error_handling/diagnostic_builder.h>

namespace ionshared {
    void DiagnosticBuilder::assertDiagnosticBufferSet() const {
        if (!this->diagnosticBuffer.has_value()) {
            throw std::runtime_error("Expected diagnostic buffer to be set");
        }
    }

    std::string DiagnosticBuilder::createTrace(Diagnostic diagnostic) noexcept {
        std::stringstream trace;

        if (diagnostic.location.has_value()) {
            Span lines = diagnostic.location->getLines();
            Span column = diagnostic.location->getColumn();

            // TODO: File path.
            trace << /*this->location.filePath +*/ ":" + std::to_string(lines.getStartPosition())
                + "-" + std::to_string(lines.getEndPosition()) + ":" + std::to_string(column.getStartPosition())
                + "-" + std::to_string(column.getEndPosition()) + " | ";
        }

        trace << DiagnosticBuilder::findDiagnosticTypeText(diagnostic.type) + ": " + diagnostic.message;

        return trace.str();
    }

    std::string DiagnosticBuilder::findDiagnosticTypeText(DiagnosticType type) {
        // TODO: Hard-coded, use a map instead?
        switch (type) {
            case DiagnosticType::InternalError: {
                return "Internal Error";
            }

            case DiagnosticType::Info: {
                return "Info";
            }

            case DiagnosticType::Warning: {
                return "Warning";
            }

            case DiagnosticType::Error: {
                return "Error";
            }

            case DiagnosticType::Fatal: {
                return "Fatal";
            }

            default: {
                return "Unknown";
            }
        }
    }

    DiagnosticBuilder::DiagnosticBuilder(Ptr<DiagnosticStack> diagnosticStack) :
        diagnosticStack(diagnosticStack),
        diagnosticBuffer(std::nullopt) {
        //
    }

    DiagnosticBuilder::DiagnosticBuilder() :
        DiagnosticBuilder(std::make_shared<DiagnosticStack>()) {
        //
    }

    Ptr<DiagnosticStack> DiagnosticBuilder::getDiagnosticStack() const noexcept {
        return this->diagnosticStack;
    }

    void DiagnosticBuilder::setDiagnosticStack(Ptr<DiagnosticStack> diagnosticStack) noexcept {
        this->diagnosticStack = diagnosticStack;
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

    Ptr<DiagnosticBuilder> DiagnosticBuilder::begin(DiagnosticType type, std::string message, std::optional<SourceLocation> location) noexcept {
        return this->begin(Diagnostic{
            type,
            message,
            location
        });
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginInfo(std::string message, std::optional<SourceLocation> location) noexcept {
        return this->begin(DiagnosticType::Info, message, location);
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginWarning(std::string message, std::optional<SourceLocation> location) noexcept {
        return this->begin(DiagnosticType::Warning, message, location);
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginError(std::string message, std::optional<SourceLocation> location) noexcept {
        return this->begin(DiagnosticType::Error, message, location);
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginFatal(std::string message, std::optional<SourceLocation> location) noexcept {
        return this->begin(DiagnosticType::Fatal, message, location);
    }

    bool DiagnosticBuilder::internalAssert(bool condition) noexcept {
        if (!condition) {
            this->begin(DiagnosticType::InternalError, "Internal assertion failed")
                ->finish();
        }

        return condition;
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::setCode(std::optional<uint32_t> code) {
        this->assertDiagnosticBufferSet();
        this->diagnosticBuffer->code = code;

        return this->shared_from_this();
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::setExample(std::optional<std::string> example) {
        this->assertDiagnosticBufferSet();
        this->diagnosticBuffer->example = example;

        return this->shared_from_this();
    }

    bool DiagnosticBuilder::finish() {
        // TODO: Should it clear buffer after finish?

        this->assertDiagnosticBufferSet();
        this->diagnosticStack->push(*this->diagnosticBuffer);

        return false;
    }

    bool DiagnosticBuilder::bootstrap(Diagnostic diagnostic, std::optional<SourceLocation> sourceLocation) {
        Diagnostic newDiagnostic = Diagnostic{
            diagnostic.type,
            diagnostic.message,
            sourceLocation,
            diagnostic.code,
            diagnostic.example
        };

        return this->begin(newDiagnostic)
            ->finish();
    }
}
