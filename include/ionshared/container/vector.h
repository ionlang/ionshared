#pragma once

#include <utility>
#include <vector>
#include <ionshared/misc/util.h>
#include <ionshared/misc/wrapper.h>

namespace ionshared {
    template<typename T>
    class Vector : public Wrapper<std::vector<T>> {
    public:
        explicit Vector(std::initializer_list<T> list) :
            Wrapper<std::vector<T>>(list) {
            //
        }

        Vector() :
            Vector({}) {
            //
        }

        T operator[](uint32_t index) {
            if (!this->value.empty() && this->value.size() > index) {
                return this->value[index];
            }

            throw std::out_of_range("Index was out of bounds");
        }

        void add(T item) {
            this->value.push_back(item);
        }

        // TODO: Missing remove function (single index, and range overloads).

        bool contains(T item) {
            return util::vectorContains(this->value, item);
        }
    };
}
