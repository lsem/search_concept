#pragma once

#include <fmt/format.h>

#include <algorithm>
#include <cstdint>
#include <llvm-expected/llvm-expected.h>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using llvm::Error;
using llvm::Expected;

using std::map;
using std::set;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

[[noreturn]] void sskit_unreachable(string what = "");
