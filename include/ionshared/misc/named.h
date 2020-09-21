#pragma once

#include <string>

namespace ionshared {
    class Named {
    private:
        std::string name;

    public:
        explicit Named(std::string name);

        [[nodiscard]] std::string getName() const noexcept;

        void setName(std::string name) noexcept;
    };
}
