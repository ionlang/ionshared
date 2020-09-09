#pragma once

#include <string>
#include <vector>
#include <ionshared/misc/helpers.h>
#include <ionshared/container/stack.h>
#include "source_location.h"

namespace ionshared {
    enum class NoticeType {
        /**
         * An internal error of the compiler. These errors are meant
         * to be debugged and fixed by the compiler developer(s).
         * Internal compiler errors cannot be recovered from because
         * they are essential.
         */
        InternalError,

        /**
         * An information notice meant to inform the user.
         */
        Info,

        Warning,

        Error,

        Fatal
    };

    /**
     * Holds valuable information about information messages, warnings,
     * errors, etc. Contains the type of notice and the message.
     */
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

        /**
         * Create a visual trace of the notice in textual form.
         */
        [[nodiscard]] std::string createTrace() const noexcept;
    };

    typedef Stack<Notice> NoticeStack;
}
