#pragma once

#include <string>
#include <llvm/IR/Module.h>
#include <ionshared/misc/wrapper.h>
#include "llvm_context.h"

namespace ionshared {
    class LlvmModule : public Wrapper<llvm::Module *> {
    private:
        LlvmContext *context;

    public:
        LlvmModule(llvm::Module *module, LlvmContext *context);

        explicit LlvmModule(llvm::Module *module);

        ~LlvmModule();

        std::string getId() const;

        LlvmContext *getContext() const;

        std::string getAsString() const;

        void print();

        void printToLlvmErrs() const;
    };
}
