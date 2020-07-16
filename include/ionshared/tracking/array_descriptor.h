#pragma once

#include <ionir/construct/type.h>

namespace ionshared {
    struct ArrayDescriptor {
        Ptr<Type> type;

        uint32_t size;
    };
}
