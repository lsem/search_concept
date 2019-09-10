
#include <gtest/gtest.h>
#include <srchlib/dal/dal.h>

#include <gflags/gflags.h>

#include <iostream>
#include <string>
#include <tuple>


std::tuple<int, int, std::string> test() {
    return {10, 30, "40"};
}


std::vector<std::tuple<int, int, std::string>> test2() {
    return {{10, 30, "40"}};
}


TEST(DalUnitTests, basic) {
    EXPECT_TRUE(true);

    for (auto [x,y,z] : test2()) {



    }

    //    dal::load_tile();
}
