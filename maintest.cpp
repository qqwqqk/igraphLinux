#include <gtest/gtest.h>
#include "header/func.h"

TEST(testCase, test0){
  EXPECT_EQ(add(2,3), 5);
}
