# ------------------------------------------------------------------
#  Dependencies
# ------------------------------------------------------------------
hunter_add_package(gflags)
find_package(gflags CONFIG REQUIRED)

# ------------------------------------------------------------------
#  Target: compiler
# ------------------------------------------------------------------
add_executable(compiler "${CMAKE_SOURCE_DIR}/src/apps/compiler/compiler_main.cpp")
set_target_properties(compiler PROPERTIES CXX_STANDARD 17)
target_link_libraries(compiler PUBLIC gflags)
