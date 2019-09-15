#pragma once

namespace apps::compiler {

class IOSMStreamReadSink {
 public:
  virtual ~IOSMStreamReadSink() = default;
  virtual void node_parsed() = 0;
  virtual void way_parsed() = 0;
  virtual void relation_parsed() = 0;
};

class IOSMStreamRead {
 public:
  virtual ~IOSMStreamRead() = default;
  // Starts reading OSM data till the end of stream. Delivers callbacks to IOSMStreamReadSink.
  virtual Error read(const string& path) = 0;
};

// Creates instance of OSMStreamRead.
// Argument path expected to be a valid path to either .pbf or .xml OSM data file.
Expected<unique_ptr<IOSMStreamRead>> create_osm_stream_read(IOSMStreamReadSink& sink);
}  // namespace apps::compiler
