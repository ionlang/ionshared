#pragma once

#include "visibility_modifier.h"
#include "local_var_descriptor.h"

namespace ionshared {
    struct FieldDescriptor : LocalVariableDescriptor {
        VisibilityModifier visibility;
    };
}
