#pragma once

#include <ionshared/misc/span.h>

namespace ionshared {
    class SourceLocation {
    private:
        Span lines;

        Span column;

    public:
        SourceLocation(Span lines, Span columns);

        [[nodiscard]] Span getLines() const noexcept;

        [[nodiscard]] Span getColumn() const noexcept;
    };
}
