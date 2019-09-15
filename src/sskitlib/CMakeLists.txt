# ------------------------------------------------------------------
#  Dependencies
# ------------------------------------------------------------------
hunter_add_package(fmt)
find_package(fmt CONFIG REQUIRED)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
find_package(GMock CONFIG REQUIRED)

# ------------------------------------------------------------------
#  Target: sskit_lib(SSKit::lib)
# ------------------------------------------------------------------
file(GLOB_RECURSE SSKITLIB_H_FILES  CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE SSKITLIB_CPP_FILES  CONFIGURE_DEPENDS "*.cpp")
# Remove tests files, they are handled in schrlib_tests target.
list(FILTER SSKITLIB_CPP_FILES EXCLUDE REGEX "_tests\\.cpp")
list(FILTER SSKITLIB_H_FILES EXCLUDE REGEX "_tests\\.h")

add_library(sskit_lib ${SSKITLIB_H_FILES} ${SSKITLIB_CPP_FILES})
add_library(SSKit::lib ALIAS sskit_lib)
set_target_properties(sskit_lib PROPERTIES CXX_STANDARD ${SSKIT_CXX_STANDARD})
target_include_directories(sskit_lib PUBLIC include)
target_link_libraries(sskit_lib PUBLIC SSKit::common)

# ------------------------------------------------------------------
#  Target: sskit_lib_tests(SSKit::lib_tests)
# ------------------------------------------------------------------
file(GLOB_RECURSE  LIB_TEST_CPP_FILES CONFIGURE_DEPENDS "*.cpp")
# Make sure only headers and cpps from tests/ subfolder are collectedsrchlib into srchlib_tests target.
list(FILTER LIB_TEST_CPP_FILES INCLUDE REGEX "(.*\\/src\\/sskitlib)(.*)(\\/tests\\/)(.*\\.cpp)")
file(GLOB_RECURSE  LIB_TEST_HEADER_FILES CONFIGURE_DEPENDS "*.h")
list(FILTER LIB_TEST_HEADER_FILES INCLUDE REGEX "(.*\\/src\\/sskitlib)(.*)(\\/tests\\/)(.*\\.h)")

add_library(sskit_lib_tests ${LIB_TEST_HEADER_FILES} ${LIB_TEST_CPP_FILES})
add_library(SSKit::lib_tests ALIAS sskit_lib_tests)
set_target_properties(sskit_lib_tests PROPERTIES CXX_STANDARD ${SSKIT_CXX_STANDARD})
target_link_libraries(sskit_lib_tests PUBLIC SSKit::lib)
target_link_libraries(sskit_lib_tests PUBLIC GMock::gmock)  # GTest::gtest will be linked automatically