#include <ionshared/error_handling/notice.h>

namespace ionshared {
    std::string Notice::getText(NoticeType type) {
        // TODO: Hard-coded, use a map instead?
        switch (type) {
            case NoticeType::Warning: {
                return "Warning";
            }

            case NoticeType::Error: {
                return "Error";
            }

            case NoticeType::Fatal: {
                return "Fatal";
            }

            default: {
                return "Unknown";
            }
        }
    }

    Notice::Notice(NoticeContext context, NoticeType type, std::string message)
        : context(context), type(type), message(message) {
        //
    }

    NoticeContext Notice::getContext() const noexcept {
        return this->context;
    }

    NoticeType Notice::getType() const noexcept {
        return this->type;
    }

    std::string Notice::getMessage() const noexcept {
        return this->message;
    }

    std::string Notice::createTrace() const noexcept {
        return this->context.filePath + ":" + std::to_string(this->context.lineNumber) + ":" +
            std::to_string(this->context.position) + " | " + Notice::getText(this->type) + ": " + this->message;
    }
}
