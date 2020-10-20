#pragma once

#include <queue>
#include <concepts>
#include <stdexcept>
#include <memory>
#include <ionshared/misc/helpers.h>
#include <ionshared/passes/base_pass.h>

namespace ionshared {
    template<typename T>
    using Ast = std::vector<Ptr<T>>;

    template<typename T>
    using TraversalCallback = std::function<bool(T)>;

    template<typename TConstruct, typename TConstructKind>
    class BaseConstruct : public std::enable_shared_from_this<BaseConstruct<TConstruct, TConstructKind>> {
    private:
        typedef BaseConstruct<TConstruct, TConstructKind> This;

    public:
        const TConstructKind constructKind;

        std::optional<ionshared::SourceLocation> sourceLocation;

        std::optional<Ptr<TConstruct>> parent;

        explicit BaseConstruct(
            TConstructKind kind,
            std::optional<ionshared::SourceLocation> sourceLocation = std::nullopt,
            OptPtr<TConstruct> parent = std::nullopt
        ) noexcept :
            constructKind(kind),
            sourceLocation(sourceLocation),
            parent(parent) {
            //
        }

//        virtual void accept(TPass visitor) = 0;

        [[nodiscard]] virtual bool equals(Ptr<This> other) {
            return other == this->shared_from_this();
        }

        [[nodiscard]] virtual Ast<TConstruct> getChildrenNodes() {
            // By default, construct contains no children.
            return {};
        }

        [[nodiscard]] bool isRootNode() noexcept {
            return util::hasValue(this->parent);
        }

        [[nodiscard]] bool isLeafNode() {
            return this->getChildrenNodes().empty();
        }

        // TODO
//        void traverseChildren(TraversalCallback<Ptr<This>> callback) {
//            std::queue<Ptr<This>> childrenQueue = {};
//            Ast<This> primeChildren = this->getChildrenNodes();
//
//            // Begin with this construct's children nodes.
//            for (const auto child : primeChildren) {
//                childrenQueue.push(primeChildren);
//            }
//
//            while (!childrenQueue.empty()) {
//                Ptr<This> child = childrenQueue.front();
//                Ast<This> children = child->getChildrenNodes();
//
//                childrenQueue.pop();
//
//                for (const auto &childOfChild : children) {
//                    childrenQueue.push(childOfChild);
//                }
//
//                // Invoke the callback, and do not continue if it returns false.
//                if (!callback(child)) {
//                    return;
//                }
//            }
//        }

        [[nodiscard]] Ptr<This> fetchRoot() {
            if (!util::hasValue(this->parent)) {
                return this->shared_from_this();
            }

            std::queue<Ptr<This>> parentQueue{};

            parentQueue.push(*this->parent);

            while (!parentQueue.empty()) {
                Ptr<This> parent = parentQueue.front();

                parentQueue.pop();

                if (!util::hasValue(parent->parent)) {
                    return parent;
                }

                parentQueue.push(*parent->parent);
            }
        }

        [[nodiscard]] Ptr<This> getBarePtr() {
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
}
