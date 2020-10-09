#pragma once

#include <llvm/IR/IRBuilder.h>
#include <ionshared/misc/wrapper.h>

namespace ionshared {
    struct IrBuilder : Wrapper<llvm::IRBuilder<>> {
        explicit IrBuilder(llvm::IRBuilder<> value) noexcept;
    };
}
