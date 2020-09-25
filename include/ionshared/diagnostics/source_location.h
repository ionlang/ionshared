#pragma once

#include <ionshared/misc/span.h>

namespace ionshared {
    struct SourceLocation {
        const Span lines;

        const Span column;
    };
}
