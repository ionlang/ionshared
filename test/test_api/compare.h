#pragma once

#include <iostream>
#include <array>
#include <string>
#include "util.h"
#include "../pch.h"

namespace ionshared::test::compare {
    /**
     * Compare 2 strings. Both strings are trimmed
     * before comparison.
     */
    bool strings(std::string expected, std::string actual);

    /**
     * Compare an LLVM IR output string with
     * a stored LLVM IR file. Both inputs are trimmed
     * before comparison. Returns false if the stored
     * LLVM IR file does not exist.
     */
    bool ir(std::string output, std::string fileName);
}
