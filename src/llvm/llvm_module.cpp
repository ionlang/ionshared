#include <iostream>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <ionshared/llvm/llvm_module.h>

namespace ionshared {
    LlvmModule::LlvmModule(llvm::Module* module, LlvmContext* context) :
        Wrapper(module),
        context(context) {
        //
    }

    LlvmModule::LlvmModule(llvm::Module* module)
        : LlvmModule(module, new LlvmContext(&module->getContext())) {
        //
    }

    LlvmModule::~LlvmModule() {
        delete this->context;
    }

    std::string LlvmModule::getId() const {
        // TODO: Can it possibly be null?
        return this->value->getModuleIdentifier();
    }

    void LlvmModule::setId(std::string id) {
        this->value->setModuleIdentifier(id);
    }

    LlvmContext *LlvmModule::getContext() const {
        return this->context;
    }

    std::string LlvmModule::makeIr() const {
        std::string result;

        llvm::raw_string_ostream rawStringOutputStream =
            llvm::raw_string_ostream(result);

        rawStringOutputStream << *this->value;
        rawStringOutputStream.flush();

        return result;
    }

    std::string LlvmModule::makeBitcode() {
        // TODO: Returning a binary representation as string is just awfully wrong.
        std::string result;

        llvm::raw_string_ostream rawStringStream =
            llvm::raw_string_ostream(result);
        // TODO
//        std::error_code errorCode;
//
//        llvm::raw_fd_ostream stream =
//            llvm::raw_fd_ostream("mod", errorCode,);

        // TODO: Might need to check for error.
        llvm::WriteBitcodeToFile(*this->value, rawStringStream);
        rawStringStream.flush();

        return result;
    }

    void LlvmModule::printIr() {
        std::cout << this->makeIr();
    }

    void LlvmModule::printIrToLlvmErrs() const {
        this->value->print(llvm::errs(), nullptr);
    }
}
