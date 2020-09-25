#pragma once

#include <ionshared/misc/helpers.h>
#include "pass_info.h"
#include "pass_context.h"

#define IONSHARED_PASS_ID static constexpr char passId = 0

namespace ionshared {
    // TODO: Circular.
//    template<typename T, typename TPass>
//    concept ConstructLike = requires(T t, TPass &visitor) {
//        { t.accept(visitor) } -> std::same_as<void>;
//    };

    template<typename T>
    struct BasePass {
    public:
        const Ptr<PassContext> context;

        explicit BasePass(Ptr<PassContext> context) :
            context(context) {
            //
        }

        virtual void visit(Ptr<T> node) = 0;

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
    };
}
