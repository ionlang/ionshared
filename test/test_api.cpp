#include "test_api/util.h"
#include "test_api/filesystem.h"
#include "test_api/const.h"
#include "pch.h"

using namespace ionshared::test;

TEST(TestApiTest, TrimSimpleString) {
    EXPECT_EQ(util::trim(" test "), "test");
}

TEST(TestApiTest, TrimString) {
    EXPECT_EQ(util::trim("  hello world  "), "hello world");
}

TEST(TestApiTest, LeftTrimString) {
    EXPECT_EQ(util::leftTrim("  hello world  "), "hello world  ");
}

TEST(TestApiTest, RightTrimString) {
    EXPECT_EQ(util::rightTrim("  hello world  "), "  hello world");
}

TEST(TestApiTest, JoinPaths) {
    EXPECT_EQ(fs::joinPaths("foo", "bar"), "foo/bar");
}

TEST(TestApiTest, FileExists) {
    EXPECT_TRUE(fs::exists(__FILE__));
    EXPECT_FALSE(fs::exists(".__madeup.file"));
}

TEST(TestApiTest, ResolvePath) {
    EXPECT_TRUE(fs::exists(fs::resolvePath("README.md")));
}

// TODO: Tests for resolveTestPath(...) missing.

TEST(TestApiTest, ReadFileContents) {
    std::optional<std::string> contents = fs::readFileContents(fs::resolvePath("test/data/test.txt"));

    EXPECT_TRUE(contents.has_value());
    EXPECT_EQ(*contents, ionshared::test::constant::foobar + "\n");
}

TEST(TestApiTest, ReadTestFile) {
    std::optional<std::string> contents = fs::readTestFile("data/test.txt");

    EXPECT_TRUE(contents.has_value());
    EXPECT_EQ(*contents, ionshared::test::constant::foobar + "\n");
}
