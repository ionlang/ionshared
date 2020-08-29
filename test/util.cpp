#include "pch.h"

using namespace ionshared;

TEST(UtilEscapeRegex, IgnoreNonSpecialCharacters) {
    EXPECT_EQ(util::escapeRegex("abc"), "abc");
    EXPECT_EQ(util::escapeRegex("123"), "123");
}

TEST(UtilEscapeRegex, EscapeSpecialCharacters) {
    EXPECT_EQ(util::escapeRegex("$^"), "\\$\\^");
}
