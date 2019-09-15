#include <common/pch.h>

#include "playground.h"

#include <gflags/gflags.h>

#include "osm_stream_read.h"
#include <iostream>

DEFINE_string(osm_file,
              "",
              "Path to OSM data file. Either .osm (XML) or .pbf (binary) can be passed");

using namespace std;

namespace apps::compiler::playground {

class Compiler : public IOSMStreamReadSink {
  virtual void node_parsed(OSMNode node) override {
    std::cout << fmt::format("Compiler::node_parsed: {}({},{})", node.ID, node.Latitude,
                             node.Longitude)
              << std::endl;
  }
  virtual void way_parsed(OSMWay way) override {
    std::cout << fmt::format("Compiler::way_parsed: {}(has {} tags}", way.ID, way.Tags.size())
              << std::endl;
  }
  virtual void relation_parsed(OSMRelation relation) override {
    std::cout << fmt::format("Compiler::relation_parsed: {} relates to ({} members)", relation.ID,
                             relation.Members.size())
              << std::endl;
  }
};

void run() {
  cout << "FLAGS_osm_file: " << FLAGS_osm_file << endl;
  Compiler compiler;

  auto stream_read = create_osm_stream_read(compiler);
  if (!stream_read) {
    cerr << fmt::format("Cannot create osm read interface. Error: {0}",
                        llvm::toString(stream_read.takeError()))
         << endl;
    return;
  }

  auto& stream_read_obj = **stream_read;
  if (auto err = stream_read_obj.read(FLAGS_osm_file)) {
    cerr << fmt::format("Failed reading osm. Error: {0}", llvm::toString(std::move(err))) << endl;
    return;
  }
}
}  // namespace apps::compiler::playground
