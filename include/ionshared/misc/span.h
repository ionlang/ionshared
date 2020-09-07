#pragma once

#include <string>

namespace ionshared {
    class Span {
    private:
        uint32_t startPosition;

        uint32_t length;

    public:
        Span(uint32_t startPosition, uint32_t length);

        [[nodiscard]] uint32_t getStartPosition() const noexcept;

        [[nodiscard]] uint32_t getEndPosition() const noexcept;

        [[nodiscard]] uint32_t getLength() const noexcept;

        [[nodiscard]] bool overlapsWith(Span span) const;

        [[nodiscard]] Span createSubSpan(uint32_t startPosition, uint32_t length) const;
    };
}
