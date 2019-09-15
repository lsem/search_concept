# ------------------------------------------------------------------
#  Dependencies
# ------------------------------------------------------------------
hunter_add_package(ZLIB)
find_package(ZLIB CONFIG REQUIRED)

hunter_add_package(Expat)
find_package(Expat CONFIG REQUIRED)

# ------------------------------------------------------------------
#  Target: giagis_readosm(GAIAGIS::readosm)
# ------------------------------------------------------------------
set(READOSM_C_FILES src/osm_objects.c src/osmxml.c src/protobuf.c src/readosm.c)
set(READOSM_H_FILES headers/readosm.h headers/readosm_internals.h headers/readosm_protobuf.h)

add_library(giagis_readosm ${READOSM_H_FILES} ${READOSM_C_FILES})
add_library(GAIAGIS::readosm ALIAS giagis_readosm)

target_compile_definitions(giagis_readosm PRIVATE _DONT_USE_CONFIG)
target_include_directories(giagis_readosm PUBLIC headers/)
target_link_libraries(giagis_readosm ZLIB::zlib)
target_link_libraries(giagis_readosm Expat)




