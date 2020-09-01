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

        bool insert(T item) {
            if (this->contains(item)) {
                return false;
            }

            /**
             * TODO: std::set's native insert() method returns
             * a pair (and possibly nullptr if it failed)? If so,
             * determine result through it.
             */
            this->value.insert(item);

            return true;
        }

        bool remove(T item) {
            if (this->contains(item)) {
                this->value.erase(item);
            }

            // TODO: Redundant check.
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
