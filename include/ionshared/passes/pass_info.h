#pragma once

#include <ionshared/container/tag_map.h>
#include "pass_like.h"

namespace ionshared {
    typedef const char * PassId;

    class PassInfo {
    private:
        // TODO: What if that PassId (T::id) goes out of scope, and the memory is freed? Will it ever 'go out of scope' if it's a static member?
        Set<PassId> requirements;

        Set<PassId> invalidations;

    public:
        PassInfo();

        [[nodiscard]] Set<PassId> getRequirements() const noexcept;

        /**
         * Add a requirement to the pass associated with this instance
         * which means that such requirement pass must already be registered
         * on the pass manager in order for the associated pass to be registered.
         */
        template<PassLike T>
        bool addRequirement() {
            return this->requirements.add(&T::id);
        }

        [[nodiscard]] Set<PassId> getInvalidations() const noexcept;

        template<PassLike T>
        bool addInvalidation() {
            return this->invalidations.add(T::id);
        }

        // TODO: Invalidates all.
    };
}
