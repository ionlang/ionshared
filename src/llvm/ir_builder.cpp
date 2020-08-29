#include <utility>
#include <ionshared/llvm/ir_builder.h>

namespace ionshared {
    IrBuilder::IrBuilder(llvm::IRBuilder<> value) :
        Wrapper(std::move(value)) {
        //
    }
}
