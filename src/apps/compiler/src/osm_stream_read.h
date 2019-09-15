#pragma once

namespace apps::compiler {

// TODO: Consider strong/tagged typedefs.
using NodeID = long long;
using WayID = long long;
using RelationID = long long;
// Represents ID that can be any object, e.g. variant<NodeID, WayID, RelationID>
using ReferencedObjectID = long long;

struct OSMTag {
  OSMTag(string key, string value) : Key(std::move(key)), Value(std::move(value)) {}
  string Key;
  string Value;
};

enum class OSMMemberType { Node, Way, Relation };

struct OSMRelationMember {
  OSMRelationMember(OSMMemberType type, ReferencedObjectID id, string role)
      : Type(type), ReferencedID(id), Role(role) {}
  OSMMemberType Type;
  ReferencedObjectID ReferencedID;
  string Role;
};

struct OSMNode {
  NodeID ID;
  double Latitude;
  double Longitude;
  int Version;
  long long ChangeSet;
  vector<OSMTag> Tags;
};

struct OSMWay {
  WayID ID;
  int Version;
  long long ChangeSet;
  vector<NodeID> NodeRefs;
  vector<OSMTag> Tags;
};

struct OSMRelation {
  RelationID ID;
  int Version;
  long long ChangeSet;
  vector<OSMRelationMember> Members;
  vector<OSMTag> Tags;
};

class IOSMStreamReadSink {
 public:
  virtual ~IOSMStreamReadSink() = default;
  virtual void node_parsed(OSMNode node) = 0;
  virtual void way_parsed(OSMWay way) = 0;
  virtual void relation_parsed(OSMRelation relation) = 0;
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
