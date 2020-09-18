#include <ionshared/tracking/scoped.h>
#include <ionshared/passes/base_pass_manager.h>
#include "pch.h"

using namespace ionshared;

typedef int TestConstruct;

class Pass : public BasePass<TestConstruct> {
public:
    IONSHARED_PASS_ID;

    Pass() :
        BasePass<TestConstruct>(nullptr) {
        //
    }
};

class PassWithRequirement : public BasePass<TestConstruct> {
public:
    IONSHARED_PASS_ID;

    PassWithRequirement() :
        BasePass<TestConstruct>(nullptr) {
        //
    }

    void initialize(PassInfo &info) override {
        info.addRequirement<Pass>();
    }
};

typedef BasePassManager<BasePass<TestConstruct>, TestConstruct> TestBasePassManager;

TEST(BasePassManagerTest, RegisterPassWithoutInit) {
    TestBasePassManager basePassManager = TestBasePassManager();

    basePassManager.registerPassWithoutInit(std::make_shared<Pass>());

    EXPECT_EQ(basePassManager.getPasses().size(), 1);
}

TEST(BasePassManagerTest, RegisterPassWithoutInitMultipleTimes) {
    TestBasePassManager basePassManager = TestBasePassManager();

    EXPECT_TRUE(basePassManager.registerPassWithoutInit(std::make_shared<Pass>()));
    EXPECT_FALSE(basePassManager.registerPassWithoutInit(std::make_shared<Pass>()));
    EXPECT_EQ(basePassManager.getPasses().size(), 1);
}

TEST(BasePassManagerTest, RegisterPassWithRequirements) {
    TestBasePassManager basePassManager = TestBasePassManager();

    // First, test that the pass won't be registered without its requirement present.
    EXPECT_FALSE(basePassManager.registerPass(std::make_shared<PassWithRequirement>()));
    EXPECT_EQ(basePassManager.getPasses().size(), 0);

    // Then, register its requirement first then the pass.
    EXPECT_TRUE(basePassManager.registerPass(std::make_shared<Pass>()));
    EXPECT_TRUE(basePassManager.registerPass(std::make_shared<PassWithRequirement>()));
    EXPECT_EQ(basePassManager.getPasses().size(), 2);
}

TEST(BasePassManagerTest, IsRegistered) {
    TestBasePassManager basePassManager = TestBasePassManager();

    EXPECT_FALSE(basePassManager.isRegistered<Pass>());
    EXPECT_TRUE(basePassManager.registerPassWithoutInit(std::make_shared<Pass>()));
    EXPECT_TRUE(basePassManager.isRegistered<Pass>());
    EXPECT_EQ(basePassManager.getPasses().size(), 1);
}
