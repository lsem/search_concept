# ------------------------------------------------------------------
#  Dependencies
# ------------------------------------------------------------------
hunter_add_package(fmt)
find_package(fmt CONFIG REQUIRED)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
find_package(GMock CONFIG REQUIRED)

# ------------------------------------------------------------------
#  Target: schrlib
# ------------------------------------------------------------------
file(GLOB_RECURSE SRCHLIB_H_FILES  CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/srchlib/*.h")
file(GLOB_RECURSE SRCHLIB_CPP_FILES  CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/srchlib/*.cpp")
# Remove tests files, they are handled in schrlib_tests target.
list(FILTER SRCHLIB_CPP_FILES EXCLUDE REGEX "_tests\\.cpp")
list(FILTER SRCHLIB_H_FILES EXCLUDE REGEX "_tests\\.h")

add_library(srchlib ${SRCHLIB_H_FILES} ${SRCHLIB_CPP_FILES})
set_target_properties(srchlib PROPERTIES CXX_STANDARD 20)
target_include_directories(srchlib PUBLIC include)
target_link_libraries(srchlib PUBLIC fmt::fmt)

# ------------------------------------------------------------------
#  Target: schrlib_tests
# ------------------------------------------------------------------
file(GLOB_RECURSE  LIB_TEST_CPP_FILES CONFIGURE_DEPENDS "*.cpp")
# Make sure only headers and cpps from tests/ subfolder are collected into srchlib_tests target.
list(FILTER LIB_TEST_CPP_FILES INCLUDE REGEX "(.*\\/src\\/srchlib)(.*)(\\/tests\\/)(.*\\.cpp)")
file(GLOB_RECURSE  LIB_TEST_HEADER_FILES CONFIGURE_DEPENDS "*.h")
list(FILTER LIB_TEST_HEADER_FILES INCLUDE REGEX "(.*\\/src\\/srchlib)(.*)(\\/tests\\/)(.*\\.h)")

add_library(srchlib_tests ${LIB_TEST_HEADER_FILES} ${LIB_TEST_CPP_FILES})
target_link_libraries(srchlib_tests PUBLIC srchlib)
target_link_libraries(srchlib_tests PUBLIC GMock::gmock)  # GTest::gtest will be linked automatically
