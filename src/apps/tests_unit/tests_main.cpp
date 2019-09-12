#include <gflags/gflags.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <limits>

// Just for testing: we can easily have extra options for unit tests.
DEFINE_bool(attach_debugger, false, "Attach debugger");

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    ::gflags::ParseCommandLineFlags(&argc, &argv, true);

    return RUN_ALL_TESTS();
}
