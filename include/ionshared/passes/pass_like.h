#pragma once

namespace ionshared {
    // TODO: What if pass_info.h is never included?
    class PassInfo;

    template<const char> using constexprHelper = void;

    template<typename T>
    concept PassLike = requires(T t, PassInfo &info) {
        T::id;

        /**
        * Ensure that member 'id' is usable in a context that requires
        * a constexpr.
        */
        typename constexprHelper<T::id>;

        //        std::derived_from<T, BasePass<TConstruct>>;

        /**
         * Specify that T must have a member named 'id' and require
         * that the type of member 'id' is const char.
         */
//        { T::id } -> std::same_as<const char>;

        { t.initialize(info) } -> std::same_as<void>;

//        { t.visit(t) } -> std::same_as<void>;
    };
}
