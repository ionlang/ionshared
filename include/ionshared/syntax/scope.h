#pragma once

#include <ionshared/construct/base_construct.h>
#include <ionshared/misc/wrapper.h>
#include <ionshared/misc/helpers.h>

namespace ionshared {
    enum class ScopeKind {
        Block
    };

    struct Scope : Wrapper<std::shared_ptr<Construct>> {
        const ScopeKind kind;

        Scope(std::shared_ptr<Construct> value, ScopeKind kind);
    };
}
