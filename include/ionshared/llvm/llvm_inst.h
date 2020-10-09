#pragma once

#include <llvm/IR/Instruction.h>
#include <ionshared/misc/wrapper.h>
#include <ionshared/misc/safe_wrapper.h>

namespace ionshared {
    struct LlvmInst : SafeWrapper<llvm::Instruction*> {
        explicit LlvmInst(llvm::Instruction* value);

        std::string getId() const;
    };
}
