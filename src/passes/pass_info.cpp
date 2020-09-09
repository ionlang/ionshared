#include <ionshared/passes/pass_info.h>

namespace ionshared {
    PassInfo::PassInfo() :
        requirements(),
        invalidations() {
        //
    }

    Set<PassId> PassInfo::getRequirements() const noexcept {
        return this->requirements;
    }

    Set<PassId> PassInfo::getInvalidations() const noexcept {
        return this->invalidations;
    }
}
