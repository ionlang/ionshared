#pragma once

#include <string>
#include "notice.h"

namespace ionshared {
    struct Diagnostic {
        Notice notice;

        std::optional<uint32_t> code;

        std::optional<std::string> example;
    };

    /**
     * Helper class to easily bootstrap notices and diagnostics.
     */
    class DiagnosticBuilder : public std::enable_shared_from_this<DiagnosticBuilder> {
    private:
        OptPtr<NoticeStack> noticeStack;

        std::optional<Diagnostic> diagnosticBuffer;

        void assertDiagnosticBufferSet() const;

    public:
        explicit DiagnosticBuilder(Ptr<NoticeStack> noticeStack);

        [[nodiscard]] OptPtr<NoticeStack> getNoticeStack() const noexcept;

        void setNoticeStack(Ptr<NoticeStack> sourceLocation) noexcept;

        [[nodiscard]] std::optional<Diagnostic> getDiagnosticBuffer() const noexcept;

        void setDiagnosticBuffer(std::optional<Diagnostic> diagnosticBuffer) noexcept;

        void clearDiagnosticBuffer() noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> begin(Diagnostic diagnostic) noexcept;

        [[nodiscard]] Ptr<DiagnosticBuilder> begin(
            NoticeType type,
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
