#pragma once

#include <variant>
#include <optional>

namespace ionshared {
    template<typename TValue, typename TError>
    class Result {
    private:
        std::variant<TValue, TError> valueOrError;

    public:
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

        bool hasValue() const noexcept {
            return std::holds_alternative<TValue>(this->valueOrError);
        }

        std::variant<TValue, TError> getValueOrError() const noexcept {
            return this->valueOrError;
        }

        std::optional<TValue> getValue() {
            if (this->hasValue()) {
                return this->valueOrError;
            }

            return std::nullopt;
        }

        std::optional<TError> getError() {
            if (!this->hasValue()) {
                return this->valueOrError;
            }

            return std::nullopt;
        }
    };
}
