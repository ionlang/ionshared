#pragma once

#include <llvm/IR/LLVMContext.h>
#include <ionshared/misc/wrapper.h>

namespace ionshared {
    class Context : public Wrapper<llvm::LLVMContext *> {
    public:
        explicit Context(llvm::LLVMContext *context);
    };
}
