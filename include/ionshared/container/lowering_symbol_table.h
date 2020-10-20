#pragma once

#include <concepts>
#include <memory>
#include <ionshared/container/map.h>

namespace ionshared {
    /**
     * A specialized symbol table (map) container for use with
     * lowering passes to keep track and lookup emitted constructs.
     */
    template<typename TConstruct, typename TLowerConstruct>
    struct LoweringSymbolTable : Wrapper<Map<TConstruct, TLowerConstruct>> {
        LoweringSymbolTable() noexcept :
            Wrapper<Map<TConstruct, TLowerConstruct>>(Map<TConstruct, TLowerConstruct>{}) {
            //
        }

        bool set(TConstruct construct, TLowerConstruct lowerConstruct) {
            if (construct == nullptr || lowerConstruct == nullptr) {
                throw std::runtime_error("Neither key nor value can be nullptr");
            }

            this->value.set(construct, lowerConstruct);
        }

        [[nodiscard]] bool contains(TConstruct construct) const {
            return this->value.contains(construct);
        }

        // TODO: Require that T is a pointer? Since pointer casts occur.
        template<typename T = TLowerConstruct>
//            require std::derived_from<T, TLowerConstruct>
        [[nodiscard]] std::optional<std::shared_ptr<T>> find(
            TConstruct construct,
            bool useDynamicCast = true
        ) {
            if (!this->contains(construct)) {
                return std::nullopt;
            }

            TLowerConstruct lookupResult = *this->value.lookup(construct);

            std::shared_ptr<T> castResult = useDynamicCast
                ? std::dynamic_pointer_cast<T>(lookupResult)
                : std::static_pointer_cast<T>(lookupResult);

            if (castResult == nullptr) {
                throw std::runtime_error("Result cast failed");
            }

            return castResult;
        }
    };
}
