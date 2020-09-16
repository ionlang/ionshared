#include <sstream>
#include <ionshared/error_handling/notice.h>

namespace ionshared {
    std::string Notice::findNoticeTypeText(NoticeType type) {
        // TODO: Hard-coded, use a map instead?
        switch (type) {
            case NoticeType::InternalError: {
                return "Internal Error";
            }

            case NoticeType::Info: {
                return "Info";
            }

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

    Notice::Notice(NoticeType type, std::string message, std::optional<SourceLocation> location) :
        type(type),
        message(message),
        location(location) {
        //
    }

    NoticeType Notice::getType() const noexcept {
        return this->type;
    }

    std::string Notice::getMessage() const noexcept {
        return this->message;
    }

    std::optional<SourceLocation> Notice::getLocation() const noexcept {
        return this->location;
    }

    std::string Notice::createTrace() const noexcept {
        std::stringstream trace;

        if (this->location.has_value()) {
            Span lines = this->getLocation()->getLines();
            Span column = this->getLocation()->getColumn();

            // TODO: File path.
            trace << /*this->location.filePath +*/ ":" + std::to_string(lines.getStartPosition())
                + "-" + std::to_string(lines.getEndPosition()) + ":" + std::to_string(column.getStartPosition())
                + "-" + std::to_string(column.getEndPosition()) + " | ";
        }

        trace << Notice::findNoticeTypeText(this->getType()) + ": " + this->getMessage();

        return trace.str();
    }
}
