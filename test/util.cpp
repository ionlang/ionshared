#include "pch.h"

using namespace ionshared;

TEST(UtilEscapeRegex, IgnoreNonSpecialCharacters) {
    EXPECT_EQ(Util::escapeRegex("abc"), "abc");
    EXPECT_EQ(Util::escapeRegex("123"), "123");
}

TEST(UtilEscapeRegex, EscapeSpecialCharacters) {
    EXPECT_EQ(Util::escapeRegex("$^"), "\\$\\^");
}
