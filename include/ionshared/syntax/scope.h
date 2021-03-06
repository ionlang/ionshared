#pragma once

#include <ionshared/construct/base_construct.h>
#include <ionshared/misc/wrapper.h>
#include <ionshared/misc/helpers.h>

namespace ionshared {
    enum class ScopeKind {
        Block
    };

    class Scope : public Wrapper<Ptr<Construct>> {
        const ScopeKind kind;

        Scope(Ptr<Construct> value, ScopeKind kind);
    };
}
