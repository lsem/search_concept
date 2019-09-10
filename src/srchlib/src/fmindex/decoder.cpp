#include <string>
#include <tuple>

std::tuple<int, int, std::string> test() {
    return {10, 30, "40"};
}


namespace srchlib::fmindex {
    auto [a, b, c] = test();
}  // namespace fmindex::srchlib

