#pragma once

#include <string>
#include <ionir/construct/type.h>

namespace ionshared {
    struct LocalVariableDescriptor {
        std::string name;

        Ptr<Type> type;
    };
}
