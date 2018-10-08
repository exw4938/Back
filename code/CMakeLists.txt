cmake_minimum_required (VERSION 3.0)
project (back)

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build/bin)
endif()

set(TEST_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/build/tests)

set(back_VERSION_MAJOR 0)
set(back_VERSION_MINOR 1)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/cmake/backConfig.h.in"
    "${PROJECT_BINARY_DIR}/backConfig.h"
)


file(COPY ${PROJECT_SOURCE_DIR}/src/config DESTINATION ${RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${PROJECT_SOURCE_DIR}/tests/configs DESTINATION ${TEST_OUTPUT})

include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory("${PROJECT_SOURCE_DIR}/src")
add_subdirectory("${PROJECT_SOURCE_DIR}/tests")

include(CTest)

set(BIN bin)

add_test(BackRuns ${BIN}/back)
