# ------------------------------------------------------------------
#  Dependencies
# ------------------------------------------------------------------
# GFlags (https://gflags.github.io/gflags/)
hunter_add_package(gflags)
find_package(gflags CONFIG REQUIRED)

# ------------------------------------------------------------------
#  Target: client
# ------------------------------------------------------------------
add_executable(client "${CMAKE_SOURCE_DIR}/src/apps/client/client_main.cpp")
set_target_properties(client PROPERTIES CXX_STANDARD ${SSKIT_CXX_STANDARD})
target_link_libraries(client PUBLIC SSKit::lib)
target_link_libraries(client PUBLIC gflags)

