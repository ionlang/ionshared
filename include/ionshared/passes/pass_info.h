#pragma once

#include <ionshared/container/tag_map.h>
#include "pass_like.h"

namespace ionshared {
    typedef const char * PassId;

    struct PassInfo {
        // TODO: What if that PassId (T::passId) goes out of scope, and the memory is freed? Will it ever 'go out of scope' if it's a static member?
        Set<PassId> requirements;

        Set<PassId> invalidations;

        /**
         * Add a requirement to the pass associated with this instance
         * which means that such requirement pass must already be registered
         * on the pass manager in order for the associated pass to be registered.
         */
        template<PassLike T>
        bool addRequirement() {
            return this->requirements.add(&T::passId);
        }

        template<PassLike T>
        bool addInvalidation() {
            return this->invalidations.add(&T::passId);
        }

        // TODO: Invalidates all.
    };
}
