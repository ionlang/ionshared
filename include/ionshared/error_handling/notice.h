#pragma once

#include <string>
#include <vector>
#include <ionshared/misc/helpers.h>
#include <ionshared/container/stack.h>
#include "source_location.h"

namespace ionshared {
    enum class NoticeType {
        InternalError,

        Info,

        Warning,

        Error,

        Fatal
    };

    class Notice {
    private:
        NoticeType type;

        std::string message;

        std::optional<SourceLocation> location;

    public:
        [[nodiscard]] static std::string findNoticeTypeText(NoticeType type);

        Notice(
            NoticeType type,
            std::string message,
            std::optional<SourceLocation> location = std::nullopt
        );

        [[nodiscard]] NoticeType getType() const noexcept;

        [[nodiscard]] std::string getMessage() const noexcept;

        [[nodiscard]] std::optional<SourceLocation> getLocation() const noexcept;

        [[nodiscard]] std::string createTrace() const noexcept;
    };

    typedef Stack<Notice> NoticeStack;
}
