#pragma once

#include <llvm/Support/Casting.h>
#include "stack.h"

namespace ionshared {
    template<typename T>
    struct LlvmStack : public Stack<T *> {
        template<typename TResult>
        [[nodiscard]] TResult *popAs() {
            return llvm::dyn_cast<TResult>(this->pop());
        }
    };
}
