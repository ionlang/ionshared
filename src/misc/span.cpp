#include <stdexcept>
#include <ionshared/misc/span.h>

namespace ionshared {
    Span::Span(uint32_t startPosition, uint32_t length) :
        startPosition(startPosition),
        length(length) {
        //
    }

    uint32_t Span::getStartPosition() const noexcept {
        return this->startPosition;
    }

    uint32_t Span::getEndPosition() const noexcept {
        return this->startPosition + this->length;
    }

    uint32_t Span::getLength() const noexcept {
        return this->length;
    }

    bool Span::overlapsWith(Span span) const {
        // TODO: Implement.
        throw std::runtime_error("Not implemented");
    }

    Span Span::createSubSpan(uint32_t startPosition, uint32_t length) const {
        // TODO: Implement.
        throw std::runtime_error("Not implemented");
    }
}
