#include <ionshared/llvm/llvm_block.h>

namespace ionshared {
    LlvmBlock::LlvmBlock(llvm::BasicBlock *value) noexcept :
        SafeWrapper(value),
        cachedBuilder(std::nullopt) {
        //
    }

    Ptr<IrBuilder> LlvmBlock::getBuilder() {
        if (this->cachedBuilder.has_value()) {
            return *this->cachedBuilder;
        }

        this->cachedBuilder = std::make_shared<IrBuilder>(llvm::IRBuilder<>(this->value));

        return *this->cachedBuilder;
    }

    OptPtr<LlvmInst> LlvmBlock::findTerminatorInst() const {
        llvm::Instruction *llvmTerminatorInst = this->value->getTerminator();

        if (llvmTerminatorInst != nullptr) {
            return std::make_shared<LlvmInst>(llvmTerminatorInst);
        }

        return std::nullopt;
    }
}
