#pragma once

#include <type_traits>
#include <exception>
#include <stdexcept>
#include <optional>
#include <stack>
#include <ionshared/misc/wrapper.h>

namespace ionshared {
    template<typename T>
    struct Stack : Wrapper<std::stack<T>> {
        explicit Stack(std::stack<T> value = {}) :
            Wrapper<std::stack<T>>(value) {
            //
        }

        explicit Stack(std::initializer_list<T> list) noexcept :
            Stack(std::stack<T>(list)) {
            //
        }

        ~Stack() {
            // TODO: Is there need clear an std::shared_ptr stack be?
            this->clear();
        }

        void push(T item) {
            this->value.push(item);
        }

        T pop() {
            std::optional<T> result = this->tryPop();

            if (!result.has_value()) {
                throw std::out_of_range("No more items in stack to pop");
            }

            return *result;
        }

        T popOr(T alternative) {
            std::optional<T> existingItem = this->tryPop();

            if (existingItem.has_value()) {
                return existingItem;
            }

            return alternative;
        }

        std::optional<T> tryPop() {
            // Underlying stack contains no more items to pop.
            if (this->value.empty()) {
                return std::nullopt;
            }

            T result = this->value.top();

            this->value.pop();

            return result;
        }

        [[nodiscard]] bool isEmpty() const {
            return this->value.empty();
        }

        void clear() {
            while (!this->isEmpty()) {
                std::optional<T> item = this->tryPop();

                if (item.has_value() && std::is_pointer<T>::value) {
                    item.reset();
                }
            }
        }

        [[nodiscard]] size_t getSize() const {
            return this->value.size();
        }
    };
}
