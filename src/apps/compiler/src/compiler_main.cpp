#include <gflags/gflags.h>

#include "playground.h"
#include <iostream>

DECLARE_string(osm_file);

int main(int argc, char* argv[]) {
  gflags::SetUsageMessage("Compile the database from OpenStreetMaps data");

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_osm_file.empty()) {
    std::cerr << "ERROR: OSM file is not specified\n\n";
    gflags::ShowUsageWithFlags(argv[0]);
    return 1;
  }

  apps::compiler::playground::run();
}