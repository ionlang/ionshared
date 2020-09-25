#pragma once

#include <llvm/IR/LLVMContext.h>
#include <ionshared/misc/wrapper.h>

namespace ionshared {
    struct LlvmContext : public Wrapper<llvm::LLVMContext *> {
        explicit LlvmContext(llvm::LLVMContext *context);
    };
}
