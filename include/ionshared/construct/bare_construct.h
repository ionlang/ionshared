#pragma once

#include <memory>
#include <ionshared/misc/helpers.h>

namespace ionshared {
    template<typename T>
    class BareConstruct : private std::enable_shared_from_this<BareConstruct<T>> {
    private:
        T constructKind;

    public:
        explicit BareConstruct(T kind) : constructKind(kind) {
            //
        }

        virtual bool equals(Ptr<BareConstruct<T>> other) {
            return other == this->shared_from_this();
        }

        bool isLeafNode() {
            // TODO
            //return this->getChildNodes().empty();

            throw std::runtime_error("Not implemented");
        }

        T getConstructKind() const {
            return this->constructKind;
        }

        Ptr<BareConstruct<T>> getPtr() {
            return this->shared_from_this();
        }
    };
}
