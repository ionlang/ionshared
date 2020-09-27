#pragma once

#include <ionshared/misc/span.h>

namespace ionshared {
    struct SourceLocation {
        Span lines;

        Span column;
    };
}
