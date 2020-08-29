#include <ionshared/llvm/llvm_context.h>

namespace ionshared {
    LlvmContext::LlvmContext(llvm::LLVMContext *context) :
        Wrapper(context) {
        //
    }
}
