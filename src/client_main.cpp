#include <iostream>
#include <cstdint>
#include <boost/program_options.hpp>

using namespace std;
namespace bpo = boost::program_options;

int main(int argc, char* argv[]) {
    bpo::options_description desc("OPTIONS");
    desc.add_options()
        ("help", "This help")
        ("port", bpo::value<uint16_t>(), "Port to listen on");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }

    if (vm.count("port")) {
        cout << "Port set to: " << vm["port"].as<uint16_t>() << endl;
    } else {
        cout << "Port is not set" << endl;
    }

    cout << "Client: Hello!\n" << endl;
}
