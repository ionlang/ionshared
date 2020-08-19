#pragma once

#include <string>
#include <vector>
#include <ionshared/misc/helpers.h>
#include <ionshared/container/stack.h>

namespace ionshared {
    enum class NoticeType {
        Warning,

        Error,

        Fatal
    };

    struct NoticeContext {
        std::string filePath;

        uint32_t lineNumber;

        uint32_t position;
    };

    class Notice {
    private:
        NoticeContext context;

        NoticeType type;

        std::string message;

    public:
        [[nodiscard]] static std::string getText(NoticeType type);

        Notice(NoticeContext context, NoticeType type, std::string message);

        [[nodiscard]] NoticeContext getContext() const noexcept;

        [[nodiscard]] NoticeType getType() const noexcept;

        [[nodiscard]] std::string getMessage() const noexcept;

        [[nodiscard]] std::string createTrace() const noexcept;
    };

    typedef Stack<Notice> NoticeStack;
}
