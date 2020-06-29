#include "pch.h"

// TODO: No need for this in this case, since there's no static init.

// Testing environment initialization.
int main(int argc, char **argv) {
    // Initialize Google tests.
    ::testing::InitGoogleTest(&argc, argv);

    // Run tests.
    return RUN_ALL_TESTS();
}
