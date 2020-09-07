#pragma once

#include <ionshared/misc/span.h>

namespace ionshared {
    class SourceLocation {
    private:
        uint32_t lineNumber;

        Span column;

    public:
        SourceLocation(uint32_t lineNumber, Span column);

        [[nodiscard]] uint32_t getLineNumber() const noexcept;

        [[nodiscard]] Span getColumn() const noexcept;
    };
}
