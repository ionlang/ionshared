#pragma once

#include <string>
#include <ionshared/misc/iterable.h>

namespace ionshared {
    template<typename T>
    struct BaseToken {
    private:
        const T kind;

        const std::string value;

        const uint32_t startPosition = 0;

        const uint32_t lineNumber = 0;

        [[nodiscard]] uint32_t getEndPosition() const noexcept {
            return this->startPosition + this->value.length();
        }

        bool operator==(const BaseToken<T> &other) const {
            return this->value == other.value &&
                this->kind == other.kind &&
                this->startPosition == other.startPosition;
        }

        bool operator!=(const BaseToken<T> &other) const {
            // Simplifying this causes a SIGSEGV (segmentation fault).
            return !(*this == other);
        }
    };

    template<typename T>
    using BaseTokenStream = Iterable<BaseToken<T>>;
}
