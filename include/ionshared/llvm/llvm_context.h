#pragma once

#include <llvm/IR/LLVMContext.h>
#include <ionshared/misc/wrapper.h>

namespace ionshared {
    class LlvmContext : public Wrapper<llvm::LLVMContext *> {
    public:
        explicit LlvmContext(llvm::LLVMContext *context);
    };
}
