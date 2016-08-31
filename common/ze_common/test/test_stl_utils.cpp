// Copyright (C) ETH Zurich, Wyss Zurich, Zurich Eye - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential

#include <string>
#include <vector>

#include <ze/common/stl_utils.hpp>
#include <ze/common/test_entrypoint.hpp>

TEST(StlUtilsTests, testRange)
{
  using namespace ze;

  {
    auto vec = range(10);
    EXPECT_EQ(vec.size(), 10u);
    EXPECT_EQ(vec[0], 0u);
    EXPECT_EQ(vec[9], 9u);
  }

  {
    auto vec = range(0);
    EXPECT_EQ(vec.size(), 0u);
  }

  {
    auto vec = range(3, 6);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 3u);
    EXPECT_EQ(vec[2], 5u);
  }

  {
    auto vec = range(4, 4);
    EXPECT_EQ(vec.size(), 0u);
  }
}

ZE_UNITTEST_ENTRYPOINT