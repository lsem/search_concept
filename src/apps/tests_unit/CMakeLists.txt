# ------------------------------------------------------------------
#  Dependencies
# ------------------------------------------------------------------
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
find_package(GMock CONFIG REQUIRED)

hunter_add_package(gflags)
find_package(gflags CONFIG REQUIRED)

hunter_add_package(Boost)
find_package(Boost CONFIG REQUIRED)

# ------------------------------------------------------------------
#  Target: tests_unit
# ------------------------------------------------------------------
file(GLOB_RECURSE TESTS_UNIT_H_FILES  CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE  TESTS_UNIT_CPP_FILES CONFIGURE_DEPENDS "*.cpp")

add_executable(tests_unit ${TESTS_UNIT_CPP_FILES} ${TESTS_UNIT_H_FILES})
set_target_properties(tests_unit PROPERTIES CXX_STANDARD 17)
target_link_libraries(tests_unit PUBLIC SSKit::lib)
target_link_libraries(tests_unit PUBLIC SSKit::lib_tests)
target_link_libraries(tests_unit PUBLIC Boost::boost) # Header only Boost part.
target_link_libraries(tests_unit PUBLIC GMock::gmock)  # GTest::gtest will be linked automatically
target_link_libraries(tests_unit PUBLIC gflags)
