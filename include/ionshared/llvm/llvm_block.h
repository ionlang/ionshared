#pragma once

#include <optional>
#include <llvm/IR/BasicBlock.h>
#include <ionshared/misc/wrapper.h>
#include <ionshared/misc/safe_wrapper.h>
#include <ionshared/misc/helpers.h>
#include "ir_builder.h"
#include "llvm_inst.h"

namespace ionshared {
    class LlvmBlock : public SafeWrapper<llvm::BasicBlock *> {
    private:
        OptPtr<IrBuilder> cachedBuilder;

    public:
        explicit LlvmBlock(llvm::BasicBlock *value);

        Ptr<IrBuilder> getBuilder();

        OptPtr<LlvmInst> findTerminatorInst() const;

        OptPtr<LlvmInst> findInstById(std::string id);
    };
}
