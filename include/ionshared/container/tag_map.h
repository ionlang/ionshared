#pragma once

#include "map.h"
#include "set.h"

namespace ionshared {
    // TODO: CRITICAL: Isn't this all just by value? Will changes apply? Review it may be CRITICAL.
    template<typename TKey, typename TTag>
    class TagMap {
    private:
        Map<TKey, Set<TTag>> entries;

        [[nodiscard]] Set<TTag> getOrCreate(TKey key) {
            if (this->entries.contains(key)) {
                return this->entries.lookup(key).value();
            }

            Set<TTag> tags = Set<TTag>();

            this->entries.set(key, tags);

            return tags;
        }

    public:
        TagMap() noexcept :
            entries() {
            //
        }

        bool has(TKey key, TTag tag) {
            if (!this->entries.contains(key)) {
                return false;
            }

            return this->entries.lookup(key).value().contains(tag);
        }

        bool tag(TKey key, TTag tag) {
            return this->getOrCreate(key).add(tag);
        }
    };
}
