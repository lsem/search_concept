cmake_minimum_required(VERSION 3.11)

include("cmake/HunterGate.cmake")

# HUNTER (https://github.com/ruslo/hunter/releases)
HunterGate(
   URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
   SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)

project(SearchConcept)

include("cmake/BuildOptions.cmake")

add_subdirectory(external/llvm-expected)
add_subdirectory("src/sskitlib")
add_subdirectory("src/common")
add_subdirectory("src/apps/client")
add_subdirectory("src/apps/compiler")
add_subdirectory("src/apps/tests_unit")



