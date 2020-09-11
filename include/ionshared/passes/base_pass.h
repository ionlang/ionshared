#pragma once

#include <ionshared/misc/helpers.h>
#include "pass_info.h"

#define IONSHARED_PASS_ID static constexpr char id = 0

namespace ionshared {
    // TODO: Circular.
//    template<typename T, typename TPass>
//    concept ConstructLike = requires(T t, TPass &visitor) {
//        { t.accept(visitor) } -> std::same_as<void>;
//    };

    template<typename T>
    class BasePass {
    public:
        virtual void initialize(PassInfo &info) {
            //
        }

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
//            node->accept(*this);
        }
    };
}
