#pragma once

#include <string>
#include <ionshared/misc/iterable.h>

namespace ionshared {
    template<typename T>
    class BareToken {
    private:
        T kind;

        std::string value;

        uint32_t startPosition;

        uint32_t lineNumber;

    public:
        BareToken(T kind, std::string value, uint32_t startPosition = 0, uint32_t lineNumber = 0)
            : kind(kind), value(value), startPosition(startPosition), lineNumber(lineNumber) {
            //
        }

        T getKind() const noexcept {
            return this->kind;
        }

        std::string getValue() const noexcept {
            return this->value;
        }

        uint32_t getStartPosition() const noexcept {
            return this->startPosition;
        }

        uint32_t getEndPosition() const noexcept {
            return this->startPosition + this->value.length();
        }

        uint32_t getLineNumber() const noexcept {
            return this->lineNumber;
        }

        bool operator==(const BareToken<T> &other) const {
            return this->value == other.value &&
                this->kind == other.kind &&
                this->startPosition == other.startPosition;
        }

        bool operator!=(const BareToken<T> &other) const {
            return *this != other;
        }
    };

    template<typename T>
    using BareTokenStream = Iterable<BareToken<T>>;
}
