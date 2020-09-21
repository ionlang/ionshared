#pragma once

#include <concepts>
#include <stdexcept>
#include <memory>
#include <ionshared/misc/helpers.h>
#include <ionshared/passes/base_pass.h>

namespace ionshared {
    template<typename TConstruct, typename TConstructKind>
    class BaseConstruct : public std::enable_shared_from_this<BaseConstruct<TConstruct, TConstructKind>> {
    private:
        TConstructKind constructKind;

    public:
        explicit BaseConstruct(TConstructKind kind) :
            constructKind(kind) {
            //
        }

        virtual void accept(BasePass<TConstruct> visitor) = 0;

        [[nodiscard]] virtual bool equals(Ptr<BaseConstruct<TConstruct, TConstructKind>> other) {
            return other == this->shared_from_this();
        }

        [[nodiscard]] bool isLeafNode() {
            // TODO
            //return this->getChildNodes().empty();

            throw std::runtime_error("Not implemented");
        }

        [[nodiscard]] TConstructKind getConstructKind() const {
            return this->constructKind;
        }

        [[nodiscard]] Ptr<BaseConstruct<TConstruct, TConstructKind>> getBarePtr() {
            return this->shared_from_this();
        }

        [[nodiscard]] Ptr<TConstruct> getPtr() {
            return this->nativeCast();
        }

        /**
         * Used to cast pointers to related types, for example casting
         * void* to the appropriate type.
         */
        template<typename TLike>
        [[nodiscard]] Ptr<TLike> staticCast() {
            Ptr<TLike> result = std::static_pointer_cast<TLike>(this->shared_from_this());

            if (result == nullptr) {
                throw std::runtime_error("Static pointer cast failed");
            }

            return result;
        }

        /**
         * Used to convert pointers and references at runtime.
         * Should be generally used for casting a pointer or reference
         * up or down an inheritance chain (inheritance hierarchy).
         */
        template<class TLike>
        [[nodiscard]] Ptr<TLike> dynamicCast() {
            Ptr<TLike> result = std::dynamic_pointer_cast<TLike>(this->shared_from_this());

            if (result == nullptr) {
                throw std::runtime_error("Dynamic pointer cast failed");
            }

            return result;
        }

        [[nodiscard]] Ptr<TConstruct> nativeCast() {
            return this->dynamicCast<TConstruct>();
        }
    };

    template<typename TDerived, typename TConstruct, typename TConstructKind>
    concept BaseConstructLike = std::derived_from<TDerived, BaseConstruct<TConstruct, TConstructKind>>;

    template<typename T>
    using Ast = std::vector<Ptr<T>>;
}
