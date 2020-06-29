#pragma once

#include <map>
#include <string>
#include <optional>
#include <memory>
#include <vector>

namespace ionshared {
    template<typename T>
    using Ptr = std::shared_ptr<T>;

    template<typename T>
    using ConstPtr = Ptr<const T>;

    template<typename T>
    using OptPtr = std::optional<Ptr<T>>;
}
