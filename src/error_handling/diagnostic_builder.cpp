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

    void DiagnosticBuilder::setNoticeStack(ionshared::Ptr<NoticeStack> noticeStack) noexcept {
        this->noticeStack = noticeStack;
    }

    std::optional<Diagnostic> DiagnosticBuilder::getDiagnosticBuffer() const noexcept {
        return this->diagnosticBuffer;
    }

    void DiagnosticBuilder::clearDiagnosticBuffer() noexcept {
        this->diagnosticBuffer = std::nullopt;
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::make(NoticeType type, std::string message, std::optional<SourceLocation> location) noexcept {
        this->diagnosticBuffer = Diagnostic{
            Notice(type, message, location)
        };

        return this->shared_from_this();
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::makeInfo(std::string message, std::optional<SourceLocation> location) noexcept {
        this->make(NoticeType::Info, message, location);

        return this->shared_from_this();
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::makeWarning(std::string message, std::optional<SourceLocation> location) noexcept {
        this->make(NoticeType::Warning, message, location);

        return this->shared_from_this();
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::makeError(std::string message, std::optional<SourceLocation> location) noexcept {
        this->make(NoticeType::Error, message, location);

        return this->shared_from_this();
    }

    Ptr<DiagnosticBuilder> DiagnosticBuilder::makeFatal(std::string message, std::optional<SourceLocation> location) noexcept {
        this->make(NoticeType::Fatal, message, location);

        return this->shared_from_this();
    }

    bool DiagnosticBuilder::internalAssert(bool condition) noexcept {
        if (!condition) {
            this->make(NoticeType::InternalError, "Internal assertion failed");
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

    bool DiagnosticBuilder::commit() {
        if (util::hasValue(this->noticeStack)) {
            this->assertDiagnosticBufferSet();

            // TODO: Diagnostic should be pushed. It's not being used.
            this->noticeStack->get()->push(this->diagnosticBuffer->notice);
        }

        return false;
    }
}
