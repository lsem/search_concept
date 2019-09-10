#pragma once

namespace srchlib {
namespace dal {

class IDataLoader {
   protected:
    ~IDataLoader() {}

   public:
    virtual bool load_tile(int tile_id) = 0;
};

class IIndex {};

void load_tile();

}  // namespace dal
}  // namespace srchlib
