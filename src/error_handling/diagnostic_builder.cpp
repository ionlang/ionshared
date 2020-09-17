#include <ionshared/misc/util.h>
#include <ionshared/error_handling/diagnostic_builder.h>

namespace ionshared {
    void DiagnosticBuilder::assertDiagnosticBufferSet() const {
        if (!this->diagnosticBuffer.has_value()) {
            throw std::runtime_error("Expected diagnostic buffer to be set");
        }
    }

    DiagnosticBuilder::DiagnosticBuilder(Ptr<NoticeStack> noticeStack) :
        noticeStack(noticeStack),
        diagnosticBuffer(std::nullopt) {
        //
    }

    OptPtr<NoticeStack> DiagnosticBuilder::getNoticeStack() const noexcept {
        return this->noticeStack;
    }

    void DiagnosticBuilder::setNoticeStack(Ptr<NoticeStack> noticeStack) noexcept {
        this->noticeStack = noticeStack;
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

    Ptr<DiagnosticBuilder> DiagnosticBuilder::begin(NoticeType type, std::string message, std::optional<SourceLocation> location) noexcept {
        return this->begin(Diagnostic{
            Notice(type, message, location)
        });
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginInfo(std::string message, std::optional<SourceLocation> location) noexcept {
        return this->begin(NoticeType::Info, message, location);
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginWarning(std::string message, std::optional<SourceLocation> location) noexcept {
        return this->begin(NoticeType::Warning, message, location);
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginError(std::string message, std::optional<SourceLocation> location) noexcept {
        return this->begin(NoticeType::Error, message, location);
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::beginFatal(std::string message, std::optional<SourceLocation> location) noexcept {
        return this->begin(NoticeType::Fatal, message, location);
    }

    bool DiagnosticBuilder::internalAssert(bool condition) noexcept {
        if (!condition) {
            this->begin(NoticeType::InternalError, "Internal assertion failed")
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

        if (util::hasValue(this->noticeStack)) {
            this->assertDiagnosticBufferSet();

            // TODO: Diagnostic should be pushed. It's not being used.
            this->noticeStack->get()->push(this->diagnosticBuffer->notice);
        }

        return false;
    }

    bool DiagnosticBuilder::bootstrap(Diagnostic diagnostic) {
        return this->begin(diagnostic)
            ->finish();
    }
}
