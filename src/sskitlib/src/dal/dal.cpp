#include <common/pch.h>
#include "srchlib/dal/dal.h"

namespace {
Expected<map<string,string>> some_helper(vector<string> names) {
    map<string,string> result;
    return result;
}

Error failing_function() {
    return Error::success();
}
}

namespace srchlib::dal {
    void test() {
        if (auto err = some_helper({"1", "2"}).takeError()) {
            // ..
        }

        if (auto err = failing_function()) {
            // ..
        }
    }
}  // namespace sskitlib::dal
