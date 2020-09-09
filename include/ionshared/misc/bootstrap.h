#pragma once

#include <vector>
#include <ionshared/llvm/llvm_module.h>
#include <ionir/construct/inst.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>
#include <ionir/lexical/token.h>
#include <ionir/lexical/token_kind.h>
#include <ionir/syntax/parser.h>
#include <ionir/misc/helpers.h>
#include "util.h"

namespace ionshared::test::bootstrap {
    [[nodiscard]] Token token(TokenKind kind = TokenKind::Unknown);

    [[nodiscard]] TokenStream tokenStream(int amountOfItems = 1);

    [[nodiscard]] Parser parser(std::vector<Token> tokens);

    [[nodiscard]] Ptr<ionshared::LlvmModule> llvmModule(
        const std::string &identifier = "test"
    );

    [[nodiscard]] Ptr<LlvmCodegenPass> llvmCodegenPass(
        const Ptr<ionshared::LlvmModule> &module = llvmModule()
    );

    [[nodiscard]] Ptr<Function> emptyFunction(
        std::vector<Ptr<Inst>> insts = {}
    );
}
