#include <ionshared/misc/named.h>

namespace ionshared {
    Named::Named(std::string name) :
        name(name) {
        //
    }

    std::string Named::getName() const noexcept {
        return this->name;
    }

    void Named::setName(std::string name) noexcept {
        this->name = name;
    }
}
