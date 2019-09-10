# ------------------------------------------------------------------
#  Dependencies
# ------------------------------------------------------------------
hunter_add_package(gflags)
find_package(gflags CONFIG REQUIRED)

# ------------------------------------------------------------------
#  Target: compiler
# ------------------------------------------------------------------
add_executable(compiler "${CMAKE_SOURCE_DIR}/src/apps/compiler/compiler_main.cpp")
# See: https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html#prop_gbl:CMAKE_CXX_KNOWN_FEATURES
# see: https://cliutils.gitlab.io/modern-cmake/chapters/features/modules.html
set_target_properties(compiler PROPERTIES CXX_STANDARD 20)
target_link_libraries(compiler PUBLIC gflags)
