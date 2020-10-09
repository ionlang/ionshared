#pragma once

#include <optional>
#include <ionshared/misc/util.h>
#include "map.h"

namespace ionshared {
    template<typename TFirst, typename TSecond>
    struct BiMap {
        Map<TFirst, TSecond> firstMap;

        Map<TSecond, TFirst> secondMap;

        explicit BiMap(std::map<TFirst, TSecond> value = {}) :
            firstMap(Map<TFirst, TSecond>(value)),
            secondMap(Map<TSecond, TFirst>(util::flipMap<TFirst, TSecond>(value))) {
            //
        }

        bool insert(TFirst first, TSecond second, bool overwrite = false) {
            return this->firstMap.set(first, second, overwrite)
                && this->secondMap.set(second, first, overwrite);
        }

        bool insert(TSecond second, TFirst first, bool overwrite = false) {
            return this->insert(first, second, overwrite);
        }

        [[nodiscard]] std::optional<TSecond> lookup(TFirst first) {
            return this->firstMap.lookup(first);
        }

        [[nodiscard]] std::optional<TFirst> lookup(TSecond second) {
            return this->secondMap.lookup(second);
        }

        [[nodiscard]] bool contains(TFirst first) const {
            return this->firstMap.contains(first);
        }

        [[nodiscard]] bool contains(TSecond second) const {
            return this->secondMap.contains(second);
        }

        BiMap<TFirst, TSecond> merge(BiMap<TFirst, TSecond> other) {
            BiMap<TFirst, TSecond> firstMap = BiMap<TFirst, TSecond>();

            // TODO: Check for existing keys in both maps.

            for (const auto [key, value] : this->firstMap.unwrapConst()) {
                firstMap.insert(key, value);
            }

            for (const auto [key, value] : other.firstMap.unwrapConst()) {
                firstMap.insert(key, value);
            }

            return BiMap<TFirst, TSecond>(firstMap);
        }
    };
}
