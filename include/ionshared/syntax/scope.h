#pragma once

#include <ionshared/construct/base_construct.h>
#include <ionshared/misc/wrapper.h>
#include <ionshared/misc/helpers.h>

namespace ionshared {
    enum class ScopeKind {
        Block
    };

    class Scope : public Wrapper<Ptr<Construct>> {
    private:
        ScopeKind kind;

    public:
        Scope(Ptr<Construct> value, ScopeKind kind);

        ScopeKind getKind() const;
    };
}
