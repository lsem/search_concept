#include <fmt/format.h>
#include <fmt/ranges.h>
#include <gtest/gtest.h>
#include <srchlib/dal/dal.h>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

TEST(Checks, fmt_can_print_vectors_of_tuples) {
    auto f = []() -> vector<tuple<int, int, vector<tuple<float, float>>>> {
      return {
          {1, 2, {{1.0, 1.1}, {2.0, 2.1}, {3.0, 3.1}}},
          {10, 20, {{10.0, 10.1}, {20.0, 20.1}, {30.0, 30.1}}},
      };
    };

    EXPECT_EQ(
        "T: {(1, 2, {(1, 1.1), (2, 2.1), (3, 3.1)}), "
        "(10, 20, {(10, 10.1), (20, 20.1), (30, 30.1)})}",
        fmt::format("T: {}", f()));
}

