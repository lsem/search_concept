#include <common/pch.h>

#include "osm_stream_read.h"

#include "readosm.h"

namespace apps::compiler {

namespace read_osm_callbacks {

int print_node(const void* user_data, const readosm_node* node);
int print_relation(const void* user_data, const readosm_relation* relation);
int print_way(const void* user_data, const readosm_way* way);

}  // namespace read_osm_callbacks

struct OSMStreamRead : public IOSMStreamRead {
  OSMStreamRead(IOSMStreamReadSink& sink) : m_sink_ref(sink), m_osm_read_handle() {}

  ~OSMStreamRead() override {
    if (m_osm_read_handle) {
      auto ret = readosm_close(m_osm_read_handle);
      if (ret != READOSM_OK) {
        std::cerr << "ERROR: readosm_close returned close" << std::endl;
      }
    }
  }

  virtual Error read(const string& path) override {
    auto ret = readosm_open(path.c_str(), &m_osm_read_handle);
    if (ret != READOSM_OK) {
      return llvm::createStringError(fmt::format("readosm_open failed with error code: {}", ret));
    }

    ret = readosm_parse(m_osm_read_handle, (const void*)this, read_osm_callbacks::print_node,
                        read_osm_callbacks::print_way, read_osm_callbacks::print_relation);
    if (ret != READOSM_OK) {
      return llvm::createStringError(fmt::format("readosm_parse failed with error code: {}", ret));
    }

    return Error::success();
  }

 public:  // osm-read callbacks
  int print_node(const readosm_node* node) {
    m_sink_ref.node_parsed();
    return 0;
  }
  int print_relation(const readosm_relation* relation) {
    m_sink_ref.relation_parsed();
    return 0;
  }

  int print_way(const readosm_way* way) {
    m_sink_ref.way_parsed();
    return 0;
  }

 public:
  IOSMStreamReadSink& m_sink_ref;
  const void* m_osm_read_handle;
};

namespace read_osm_callbacks {

int print_node(const void* user_data, const readosm_node* node) {
  return ((OSMStreamRead*)(user_data))->print_node(node);
}
int print_relation(const void* user_data, const readosm_relation* relation) {
  return ((OSMStreamRead*)(user_data))->print_relation(relation);
}

int print_way(const void* user_data, const readosm_way* way) {
  return ((OSMStreamRead*)(user_data))->print_way(way);
}
}  // namespace read_osm_callbacks

Expected<unique_ptr<IOSMStreamRead>> create_osm_stream_read(IOSMStreamReadSink& sink) {
  return std::make_unique<OSMStreamRead>(sink);
}
}  // namespace apps::compiler
