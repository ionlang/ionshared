#pragma once

#include <ionshared/misc/helpers.h>
#include <ionshared/construct/bare_construct.h>

namespace ionshared {
    template<typename T>
    class BarePass {
    public:
        /**
         * Invoked when the pass is about to process the AST.
         */
        virtual void prepare() {
            //
        }

        /**
         * Invoked when the pass has traversed the entire AST.
         */
        virtual void finish() {
            //
        }

        virtual void visit(Ptr<T> node) {
            // TODO: Node must use generic constraints somehow to bind the accept function.
            node->accept(*this);
        }
    };
}
