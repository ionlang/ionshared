#include <ionshared/error_handling/source_location.h>

namespace ionshared {
    SourceLocation::SourceLocation(Span lines, Span columns) :
        lines(lines),
        column(columns) {
        //
    }

    Span SourceLocation::getLines() const noexcept {
        return this->lines;
    }

    Span SourceLocation::getColumn() const noexcept {
        return this->column;
    }
}
