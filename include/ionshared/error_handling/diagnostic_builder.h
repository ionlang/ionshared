#pragma once

#include <string>
#include "notice.h"

namespace ionshared {
    struct Diagnostic {
        Notice notice;

        std::optional<uint32_t> code;

        std::optional<std::string> example;
    };

class DiagnosticBuilder : public std::enable_shared_from_this<DiagnosticBuilder> {
    private:
        OptPtr<NoticeStack> noticeStack;

        std::optional<Diagnostic> diagnosticBuffer;

        void assertDiagnosticBufferSet() const;

    public:
        explicit DiagnosticBuilder(Ptr<NoticeStack> noticeStack);

        [[nodiscard]] OptPtr<NoticeStack> getNoticeStack() const noexcept;

        void setNoticeStack(ionshared::Ptr<NoticeStack> sourceLocation) noexcept;

        [[nodiscard]] std::optional<Diagnostic> getDiagnosticBuffer() const noexcept;

        void clearDiagnosticBuffer() noexcept;

        Ptr<DiagnosticBuilder> make(
            NoticeType type,
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        Ptr<DiagnosticBuilder> makeInfo(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        Ptr<DiagnosticBuilder> makeWarning(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        Ptr<DiagnosticBuilder>makeError(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        Ptr<DiagnosticBuilder> makeFatal(
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        ) noexcept;

        bool internalAssert(bool condition) noexcept;

        Ptr<DiagnosticBuilder> setCode(std::optional<uint32_t> code);

        Ptr<DiagnosticBuilder> setExample(std::optional<std::string> example);

        bool commit();
    };
}
