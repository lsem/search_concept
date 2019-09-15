#include <common/pch.h>

#include "osm_stream_read.h"

#include "readosm.h"

namespace apps::compiler {

namespace {
OSMMemberType map_member_type(int member_type) {
  switch (member_type) {
    case READOSM_MEMBER_NODE:
      return OSMMemberType::Node;
    case READOSM_MEMBER_WAY:
      return OSMMemberType::Way;
    case READOSM_MEMBER_RELATION:
      return OSMMemberType::Relation;
    default:
      ::sskit_unreachable(
          fmt::format("Unexpected member type came from readosm library: {}", member_type));
  }
}
}  // namespace

namespace read_osm_callbacks {
int handle_node(const void* user_data, const readosm_node* node);
int handle_relation(const void* user_data, const readosm_relation* relation);
int handle_way(const void* user_data, const readosm_way* way);
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

    ret = readosm_parse(m_osm_read_handle, (const void*)this, read_osm_callbacks::handle_node,
                        read_osm_callbacks::handle_way, read_osm_callbacks::handle_relation);
    if (ret != READOSM_OK) {
      return llvm::createStringError(fmt::format("readosm_parse failed with error code: {}", ret));
    }

    return Error::success();
  }

 public:  // osm-read callbacks
  int handle_node(const readosm_node* node) {
    OSMNode new_node;
    new_node.ID = node->id;
    new_node.Latitude = node->latitude;
    new_node.Longitude = node->longitude;
    new_node.Version = node->version;
    new_node.ChangeSet = node->changeset;
    for (auto i = 0; i < node->tag_count; ++i) {
      auto* tag = node->tags + i;
      new_node.Tags.emplace_back(string(tag->key), string(tag->value));
    }
    m_sink_ref.node_parsed(std::move(new_node));
    return 0;
  }

  int handle_relation(const readosm_relation* relation) {
    OSMRelation new_relation;
    new_relation.ID = relation->id;
    new_relation.Version = relation->version;
    for (auto i = 0; i < relation->member_count; ++i) {
      auto* member = relation->members + i;
      new_relation.Members.emplace_back(map_member_type(member->member_type), member->id,
                                        string(member->role));
    }
    for (auto i = 0; i < relation->tag_count; ++i) {
      auto* tag = relation->tags + i;
      new_relation.Tags.emplace_back(string(tag->key), string(tag->value));
    }
    m_sink_ref.relation_parsed(std::move(new_relation));
    return 0;
  }

  int handle_way(const readosm_way* way) {
    OSMWay new_way;
    new_way.ID = way->id;
    new_way.Version = way->version;
    new_way.ChangeSet = way->changeset;
    for (auto i = 0; i < way->node_ref_count; ++i) {
      new_way.NodeRefs.emplace_back(*(way->node_refs + i));
    }
    for (auto i = 0; i < way->tag_count; ++i) {
      auto* tag = way->tags + i;
      new_way.Tags.emplace_back(string(tag->key), string(tag->value));
    }
    m_sink_ref.way_parsed(std::move(new_way));
    return 0;
  }

 public:
  IOSMStreamReadSink& m_sink_ref;
  const void* m_osm_read_handle;
};

namespace read_osm_callbacks {
int handle_node(const void* user_data, const readosm_node* node) {
  return ((OSMStreamRead*)(user_data))->handle_node(node);
}

int handle_relation(const void* user_data, const readosm_relation* relation) {
  return ((OSMStreamRead*)(user_data))->handle_relation(relation);
}

int handle_way(const void* user_data, const readosm_way* way) {
  return ((OSMStreamRead*)(user_data))->handle_way(way);
}
}  // namespace read_osm_callbacks

Expected<unique_ptr<IOSMStreamRead>> create_osm_stream_read(IOSMStreamReadSink& sink) {
  return std::make_unique<OSMStreamRead>(sink);
}
}  // namespace apps::compiler
