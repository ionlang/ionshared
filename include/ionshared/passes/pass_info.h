#pragma once

#include <ionshared/container/tag_map.h>

namespace ionshared {
    class PassInfo;

    template<const char> using constexprHelper = void;

    template<typename T>
    concept PassLike = requires(T t, PassInfo &info) {
        /**
        * Ensure that member 'id' is usable in a context that requires
        * a constexpr.
        */
        typename constexprHelper<T::id>;

        /**
         * Specify that T must have a member named 'id' and require
         * that the type of member 'id' is const char.
         */
        { T::id } -> std::same_as<const char>;

        { t.initialize(info) } -> std::same_as<void>;
    };

    typedef const char * PassId;

    class PassInfo {
    private:
        // TODO: What if that PassId (T::id) goes out of scope, and the memory is freed? Will it ever 'go out of scope' if it's a static member?
        Set<PassId> requirements;

        Set<PassId> invalidations;

    public:
        PassInfo();

        [[nodiscard]] Set<PassId> getRequirements() const noexcept;

        template<PassLike T>
        bool addRequirement() {
            return this->requirements.add(&T::id);
        }

        [[nodiscard]] Set<PassId> getInvalidations() const noexcept;

        template<PassLike T>
        bool addInvalidation() {
            return this->invalidations.add(T::id);
        }
    };
}
