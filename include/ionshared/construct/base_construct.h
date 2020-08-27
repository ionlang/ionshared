#pragma once

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
        explicit BaseConstruct(TConstructKind kind) : constructKind(kind) {
            //
        }

        virtual void accept(BasePass<TConstruct> visitor) = 0;

        virtual bool equals(Ptr<BaseConstruct<TConstruct, TConstructKind>> other) {
            return other == this->shared_from_this();
        }

        bool isLeafNode() {
            // TODO
            //return this->getChildNodes().empty();

            throw std::runtime_error("Not implemented");
        }

        TConstructKind getConstructKind() const {
            return this->constructKind;
        }

        Ptr<BaseConstruct<TConstruct, TConstructKind>> getBarePtr() {
            return this->shared_from_this();
        }

        Ptr<TConstruct> getPtr() {
            return this->nativeCast();
        }

        /**
         * Used to cast pointers to related types, for example casting
         * void* to the appropriate type.
         */
        template<typename TLike>
        Ptr<TLike> staticCast() {
            return std::static_pointer_cast<TLike>(this->shared_from_this());
        }

        /**
         * Used to convert pointers and references at runtime.
         * Should be generally used for casting a pointer or reference
         * up or down an inheritance chain (inheritance hierarchy).
         */
        template<class TLike>
        Ptr<TLike> dynamicCast() {
            return std::dynamic_pointer_cast<TLike>(this->shared_from_this());
        }

        Ptr<TConstruct> nativeCast() {
            return this->dynamicCast<TConstruct>();
        }
    };

    template<typename T>
    using Ast = std::vector<Ptr<T>>;
}
