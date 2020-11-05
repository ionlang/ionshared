#include <ionshared/tracking/scoped.h>
#include "test_api/const.h"
#include "pch.h"

using namespace ionshared;

struct TestConstruct : BaseConstruct<TestConstruct, int> {
    //
};

typedef Scoped<TestConstruct, int> TestScoped;

TEST(ScopedTest, TraverseOnce) {
    TestScoped scope = TestScoped();
    uint32_t counter = 0;

    scope.traverseScopes([&](TestScoped &scope) -> bool {
        counter++;

        return true;
    });

    EXPECT_EQ(counter, 1);
}

TEST(ScopedTest, TraverseSelf) {
    TestScoped scope = TestScoped();
    bool flag = false;

    scope.traverseScopes([&](TestScoped &scope) -> bool {
        EXPECT_EQ(&scope, &scope);

        flag = true;

        return true;
    });

    EXPECT_TRUE(flag);
}

TEST(ScopedTest, SetHasAndGetParent) {
    TestScoped parentScope = TestScoped();
    TestScoped scope = TestScoped();

    scope.parentScope = parentScope;

    EXPECT_TRUE(parentScope.hasParentScope());
    EXPECT_EQ(&scope.parentScope.value().get(), &parentScope);
}

TEST(ScopedTest, TraverseParents) {
    TestScoped parentScope = TestScoped();
    TestScoped scope = TestScoped();
    bool prime = true;

    scope.parentScope = parentScope;

    scope.traverseScopes([&](TestScoped &scope) -> bool {
        if (prime) {
            EXPECT_EQ(&scope, &scope);

            prime = false;
        }
        else {
            EXPECT_EQ(&scope, &parentScope);
        }

        return true;
    });
}
