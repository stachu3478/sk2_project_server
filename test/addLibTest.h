#include "gtest/gtest.h"
#include "../src/addLib.h"

TEST(addLibTest, addsTwoNumbers) {
    EXPECT_EQ(add(2, 2), 4);
} 