#pragma once

#include <llvm/IR/Instruction.h>
#include <ionshared/misc/wrapper.h>
#include <ionshared/misc/safe_wrapper.h>

namespace ionshared {
    class LlvmInst : public SafeWrapper<llvm::Instruction *> {
    public:
        explicit LlvmInst(llvm::Instruction *value);

        std::string getId() const;
    };
}
