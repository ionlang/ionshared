#pragma once

#include <ionshared/misc/helpers.h>
#include "pass_info.h"

namespace ionshared {
    template<typename T>
    class BasePass {
    public:
        static constexpr char id = 0;

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
            node->accept(*this);
        }
    };

    class popo : public BasePass<int> {
    public:
    };

    class ffo : public BasePass<int> {
    public:
        void initialize(PassInfo &info) override {
            info.addRequirement<popo>();
        }
    };
}
