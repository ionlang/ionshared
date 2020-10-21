#pragma once

#include <concepts>
#include <memory>
#include <llvm/Support/Casting.h>
#include <ionshared/container/map.h>

namespace ionshared {
    enum class CastKind {
        None,

        StaticPointerCast,

        DynamicPointerCast,

        LlvmDynamicPointerCast,

        LlvmDynamicPointerOrNullCast
    };

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
            CastKind castKind = CastKind::None
        ) {
            if (!this->contains(construct)) {
                return std::nullopt;
            }

            TLowerConstruct lookupResult = *this->value.lookup(construct);

            if (castKind == CastKind::None) {
                return lookupResult;
            }

            std::shared_ptr<T> castResult{};

            switch (castKind) {
                case CastKind::DynamicPointerCast: {
                    castResult = std::dynamic_pointer_cast<T>(lookupResult);

                    break;
                }

                case CastKind::StaticPointerCast: {
                    castResult = std::static_pointer_cast<T>(lookupResult);

                    break;
                }

                // TODO: Review.
//                case CastKind::LlvmDynamicPointerCast: {
//                    castResult = std::shared_ptr<T>(
//                        llvm::dyn_cast<T>(lookupResult)
//                    );
//
//                    break;
//                }

//                case CastKind::LlvmDynamicPointerOrNullCast: {
//                    castResult = std::shared_ptr<T>(
//                        llvm::dyn_cast_or_null<T>(lookupResult)
//                    );
//
//                    break;
//                }

                default: {
                    throw std::runtime_error("Unknown cast kind");
                }
            }

            if (castResult == nullptr) {
                throw std::runtime_error("Result cast failed");
            }

            return castResult;
        }
    };
}
