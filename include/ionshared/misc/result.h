#pragma once

#include <variant>
#include <optional>
#include <ionshared/misc/helpers.h>

namespace ionshared {
    template<typename TValue, typename TError>
    class Result {
    private:
        std::variant<TValue, TError> valueOrError;

    public:
        template<typename T>
        Result(T value) :
            valueOrError(value) {
            //
        }

        explicit Result(std::variant<TValue, TError> valueOrError) :
            valueOrError(valueOrError) {
            //
        }

        Result<TValue, TError> &operator=(TValue value) {
            this->valueOrError = value;
        }

        Result<TValue, TError> &operator=(TError error) {
            this->valueOrError = error;
        }

        TValue &operator*() {
            return *this->getValue();
        }

        [[nodiscard]] bool hasValue() const noexcept {
            return std::holds_alternative<TValue>(this->valueOrError);
        }

        [[nodiscard]] std::variant<TValue, TError> getValueOrError() const noexcept {
            return this->valueOrError;
        }

        [[nodiscard]] std::optional<TValue> getValue() {
            if (this->hasValue()) {
                return this->valueOrError;
            }

            return std::nullopt;
        }

        [[nodiscard]] std::optional<TError> getError() {
            if (!this->hasValue()) {
                return this->valueOrError;
            }

            return std::nullopt;
        }
    };

    template<typename TValue, typename TError>
    using PtrResult = Ptr<Result<TValue, TError>>;
}
