#include <ionshared/tracking/scoped.h>
#include "test_api/const.h"
#include "pch.h"

using namespace ionshared;

TEST(ScopedTest, IgnoreNonSpecialCharacters) {
    class TestClass {
        //
    };

    ionshared::Ptr<Scoped<TestClass>> scope = std::make_shared<Scoped<TestClass>>();

    scope->getSymbolTable()->set(test::constant::foo, std::make_shared<TestClass>());

    // TODO: Continue implementation.
}
