#include <gflags/gflags.h>

#include <cstdint>
#include <iostream>
#include <string>

DEFINE_bool(big_menu, true, "Include 'advanced' options in the menu listing");
DEFINE_string(languages, "english,french,german",
              "comma-separated list of languages to offer in the 'lang' menu");

using namespace std;

int main(int argc, char* argv[]) {
    auto args_begin_index = gflags::ParseCommandLineFlags(&argc, &argv, true);
    cout << "Args are:\n";
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << endl;
    }
}
