#pragma once

#include <string>

namespace ionshared {
    class Named {
    private:
        std::string id;

    public:
        explicit Named(std::string id);

        [[nodiscard]] std::string getId() const noexcept;

        void setId(std::string id) noexcept;
    };
}
