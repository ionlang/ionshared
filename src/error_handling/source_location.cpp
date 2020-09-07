#include <ionshared/error_handling/source_location.h>

namespace ionshared {
    SourceLocation::SourceLocation(uint32_t lineNumber, Span column) :
        lineNumber(lineNumber),
        column(column) {
        //
    }

    uint32_t SourceLocation::getLineNumber() const noexcept {
        return this->lineNumber;
    }

    Span SourceLocation::getColumn() const noexcept {
        return this->column;
    }
}
