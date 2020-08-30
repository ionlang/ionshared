#pragma once

#include <string>
#include <ionshared/misc/iterable.h>

namespace ionshared {
    template<typename T>
    class BaseToken {
    private:
        T kind;

        std::string value;

        uint32_t startPosition;

        uint32_t lineNumber;

    public:
        BaseToken(T kind, std::string value, uint32_t startPosition = 0, uint32_t lineNumber = 0) :
            kind(kind),
            value(value),
            startPosition(startPosition),
            lineNumber(lineNumber) {
            //
        }

        [[nodiscard]] T getKind() const noexcept {
            return this->kind;
        }

        [[nodiscard]] std::string getValue() const noexcept {
            return this->value;
        }

        [[nodiscard]] uint32_t getStartPosition() const noexcept {
            return this->startPosition;
        }

        [[nodiscard]] uint32_t getEndPosition() const noexcept {
            return this->startPosition + this->value.length();
        }

        [[nodiscard]] uint32_t getLineNumber() const noexcept {
            return this->lineNumber;
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
