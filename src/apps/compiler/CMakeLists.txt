# ------------------------------------------------------------------
#  Dependencies
# ------------------------------------------------------------------
hunter_add_package(gflags)
find_package(gflags CONFIG REQUIRED)

# ------------------------------------------------------------------
#  Target: compiler
# ------------------------------------------------------------------
file(GLOB_RECURSE COMPILER_H_FILES CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE COMPILER_CPP_FILES CONFIGURE_DEPENDS "*.cpp")
add_executable(compiler ${COMPILER_H_FILES} ${COMPILER_CPP_FILES})
set_target_properties(compiler PROPERTIES CXX_STANDARD ${SSKIT_CXX_STANDARD})
target_link_libraries(compiler PUBLIC SSKit::common)
target_link_libraries(compiler PUBLIC GAIAGIS::readosm)
target_link_libraries(compiler PUBLIC gflags)
