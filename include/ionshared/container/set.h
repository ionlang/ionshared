#pragma once

#include <set>
#include <ionshared/misc/wrapper.h>

namespace ionshared {
    template<typename T>
    class Set : public Wrapper<std::set<T>> {
    public:
        explicit Set(std::set<T> value = {}) :
            Wrapper<std::set<T>>(value) {
            //
        }

        bool add(T item) {
            return this->value.insert(item).second;
        }

        bool remove(T item) {
            if (this->contains(item)) {
                this->value.erase(item);
            }

            // TODO: Redundant check?
            return this->contains(item);
        }

        [[nodiscard]] bool contains(T item) const {
            return this->value.find(item) != this->value.end();
        }

        [[nodiscard]] size_t getSize() const {
            return this->value.size();
        }

        void clear() {
            this->value.clear();
        }
    };
};
