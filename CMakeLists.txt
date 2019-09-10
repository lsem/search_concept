cmake_minimum_required(VERSION 3.11)

include("cmake/HunterGate.cmake")

# HUNTER
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.16.15.tar.gz"
    SHA1 "6974c2150fc0d3b09de3ad1efcbf15d360647ffa"
)

project(SearchConcept)


# GTEST
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
find_package(GMock CONFIG REQUIRED)

# BOOST
hunter_add_package(Boost COMPONENTS system program_options)
find_package(Boost CONFIG REQUIRED system program_options)


# SearchConcept::Tests
add_executable(Tests  "src/tests_main.cpp")
target_link_libraries(Tests PUBLIC GTest::main)
target_link_libraries(Tests PUBLIC GMock::gmock)  # GTest::gtest will be linked automatically

# SearchConcept::Compiler
add_executable(Compiler "src/compiler_main.cpp")
target_link_libraries(Compiler Boost::program_options)

# SearchConcept::Client
add_executable(Client "src/client_main.cpp")
target_link_libraries(Client PUBLIC Boost::program_options)

