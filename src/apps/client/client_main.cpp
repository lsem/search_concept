#include <gflags/gflags.h>

#include <iostream>
#include <string>

DEFINE_bool(example_flag, true, "Example flag");
DEFINE_string(example_list, "one,two,three", "An example of list (in fact just a string)");

using namespace std;

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    cout << "Args are:\n";
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << endl;
    }
}
