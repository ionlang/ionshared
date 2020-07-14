#pragma once

#include <llvm/IR/IRBuilder.h>
#include <ionshared/misc/wrapper.h>

namespace ionshared {
    class IrBuilder : public Wrapper<llvm::IRBuilder<>> {
    public:
        explicit IrBuilder(llvm::IRBuilder<> value);
    };
}
