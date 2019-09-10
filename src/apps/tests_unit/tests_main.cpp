#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <gflags/gflags.h>
#include <limits>

// Just for testing
DEFINE_bool(attach_debugger, false, "Attach debugger");

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    ::gflags::ParseCommandLineFlags(&argc, &argv, true);

    return RUN_ALL_TESTS();
}

int add(int x, int y) {
    return x + y;
}

TEST(AddTest, basic) {
    EXPECT_EQ(3, add(1, 2));
}

TEST(AddTest, negative) {
    EXPECT_EQ(-10, add(-5, -5));
}

TEST(AddTest, overflow) {
    if (FLAGS_attach_debugger) {
        std::cout << "DEBUGGER ATTACHED!\n";
    }
    EXPECT_EQ(std::numeric_limits<int>::max(),
              add(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()));
}