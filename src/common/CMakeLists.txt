# Library contains code common to entire project: global definitions, error handling, typedefs.

file(GLOB_RECURSE COMMON_H_FILES CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE COMMON_CPP_FILES CONFIGURE_DEPENDS "*.cpp")

add_library(sskit_common ${COMMON_H_FILES} ${COMMON_CPP_FILES})
add_library(SSKit::common ALIAS sskit_common)
set_target_properties(sskit_common PROPERTIES CXX_STANDARD ${SSKIT_CXX_STANDARD})
target_include_directories(sskit_common PUBLIC include)
target_link_libraries(sskit_common llvm_expected)