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

file(GLOB_RECURSE TESTS_UNIT_H_FILES  CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/apps/tests_unit/*.h")
message(STATUS "[SRCH] tests_unit headers: ${TESTS_UNIT_H_FILES}")
file(GLOB_RECURSE  TESTS_UNIT_CPP_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/apps/tests_unit/*.cpp")
message(STATUS "[SRCH] tests_unit sources: ${TESTS_UNIT_CPP_FILES}")

add_executable(tests_unit ${TESTS_UNIT_CPP_FILES}
						  ${TESTS_UNIT_H_FILES})

set_target_properties(tests_unit PROPERTIES CXX_STANDARD 20)

target_link_libraries(tests_unit PUBLIC srchlib)
target_link_libraries(tests_unit PUBLIC srchlib_tests)
target_link_libraries(tests_unit PUBLIC GMock::gmock)  # GTest::gtest will be linked automatically
target_link_libraries(tests_unit PUBLIC gflags)
target_link_libraries(tests_unit PUBLIC Boost::boost) # Header only Boost part.