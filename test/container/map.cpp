#include <string>
#include "../test_api/const.h"
#include "../pch.h"

using namespace ionshared;

constexpr int value = 1;

TEST(MapContainerTest, Initialize) {
    Map<std::string, int> map = Map<std::string, int>({{
        test::constant::foobar,
        value
    }});

    EXPECT_EQ(map.unwrap().size(), 1);
    EXPECT_EQ(map.unwrap()[test::constant::foobar], value);
}

TEST(MapContainerTest, Contains) {
    Map<std::string, int> map = Map<std::string, int>({{
        test::constant::foobar,
        value
    }});

    EXPECT_TRUE(map.contains(test::constant::foobar));
}

TEST(MapContainerTest, Insert) {
    Map<std::string, int> map = Map<std::string, int>();

    EXPECT_TRUE(map.set(test::constant::foobar, value));
    EXPECT_TRUE(map.contains(test::constant::foobar));
    EXPECT_EQ(map.unwrap()[test::constant::foobar], value);
}

TEST(MapContainerTest, Lookup) {
    Map<std::string, int> map = Map<std::string, int>({{
        test::constant::foobar,
        value
    }});

    EXPECT_EQ(map.lookup(test::constant::foobar), value);
}

TEST(MapContainerTest, LookupOr) {
    Map<std::string, int> map = Map<std::string, int>();

    EXPECT_EQ(map.lookupOr(test::constant::foobar, value), value);
}

TEST(MapContainerTest, Size) {
    Map<std::string, int> map = Map<std::string, int>();

    EXPECT_EQ(map.getSize(), 0);

    map.set(test::constant::foobar, value);

    EXPECT_EQ(map.getSize(), 1);
}

TEST(MapContainerTest, Remove) {
    Map<std::string, int> map = Map<std::string, int>({{
        test::constant::foobar,
        value
    }});

    EXPECT_EQ(map.getSize(), 1);
    EXPECT_TRUE(map.remove(test::constant::foobar));
    EXPECT_EQ(map.getSize(), 0);
    EXPECT_FALSE(map.remove(test::constant::foobar));
}
