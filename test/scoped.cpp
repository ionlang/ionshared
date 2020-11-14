#include <ionshared/tracking/scoped.h>
#include "test_api/const.h"
#include "pch.h"

using namespace ionshared;

struct TestConstruct : BaseConstruct<TestConstruct, int> {
    //
};

typedef Scoped<TestConstruct, int> TestScoped;

TEST(ScopedTest, TraverseOnce) {
    std::shared_ptr<TestScoped> scope =
        std::make_shared<TestScoped>();

    uint32_t counter = 0;

    scope->traverseScopes(scope, [&](std::shared_ptr<TestScoped> scope) -> bool {
        counter++;

        return true;
    });

    EXPECT_EQ(counter, 1);
}

TEST(ScopedTest, TraverseSelf) {
    std::shared_ptr<TestScoped> scope =
        std::make_shared<TestScoped>();

    bool wasCallbackInvoked = false;

    scope->traverseScopes(scope, [&](std::shared_ptr<TestScoped> traversingScope) -> bool {
        EXPECT_EQ(*&scope, *&traversingScope);
        wasCallbackInvoked = true;

        return true;
    });

    EXPECT_TRUE(wasCallbackInvoked);
}

TEST(ScopedTest, HasParentScope) {
    std::shared_ptr<TestScoped> parentScope =
        std::make_shared<TestScoped>();

    std::shared_ptr<TestScoped> scope =
        std::make_shared<TestScoped>();

    scope->parentScope = parentScope;

    EXPECT_TRUE(scope->hasParentScope());
}

TEST(ScopedTest, TraverseParents) {
    std::shared_ptr<TestScoped> parentScope =
        std::make_shared<TestScoped>();

    std::shared_ptr<TestScoped> scope =
        std::make_shared<TestScoped>();

    bool prime = true;

    scope->parentScope = parentScope;

    scope->traverseScopes(scope, [&](std::shared_ptr<TestScoped> traversingScope) -> bool {
        // TODO: Review/redo.
//        if (prime) {
//            EXPECT_EQ(scope, traversingScope);
//
//            prime = false;
//        }
//        else {
//            EXPECT_EQ(&scope, &parentScope);
//        }
//
//        return true;
        return true;
    });
}
