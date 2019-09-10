# COVEREGE
option(CLANG_CODE_COVEREGE "Generate Clang code coverege information (affects only Debug builds)" OFF)
if (CLANG_CODE_COVEREGE)
    # Stolen here: https://github.com/johnthagen/clang-blueprint/blob/master/cmake/clang_tools.cmake
    # AFAICS: CMAKE_CXX_FLAGS_DEBUG is built in var that used for debug builds.
    message(STATUS "[SRCH] [OPTION]: Code coverege metrics enabled in Clang")
    set(CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-instr-generate -fcoverage-mapping")
endif()

# CLANG-TIDY
find_program(CLANG_TIDY
        NAMES clang-tidy
        PATHS ENV LLVM_ROOT)
if (CLANG_TIDY)
    message(STATUS "[SearchConcept::OPTION]: clang-tify found")
    message(STATUS "[srch] [CLANG-TIDY]: here is a list ${SRCHLIB_CPP_FILES}")
    add_custom_target(
            clang-tidy
            COMMAND ${CLANG_TIDY}
            ${SRCHLIB_CPP_FILES}
            --
            -std=c++14
            -I ${SRCHLIB_H_FILES}
    )
endif()

# ADDRESS-SANITIZER
# ...