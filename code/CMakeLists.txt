cmake_minimum_required (VERSION 3.0)
project (back)

set(back_VERSION_MAJOR 0)
set(back_VERSION_MINOR 1)
set(TEST_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/build/tests)

include(CTest)

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build/bin)
endif()


configure_file (
    "${PROJECT_SOURCE_DIR}/back/cmake/backConfig.h.in"
    "${PROJECT_BINARY_DIR}/backConfig.h"
)

include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory("${PROJECT_SOURCE_DIR}/back")
add_subdirectory("${PROJECT_SOURCE_DIR}/tests")

file(COPY ${PROJECT_SOURCE_DIR}/back/config DESTINATION ${RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${PROJECT_SOURCE_DIR}/tests/configs DESTINATION ${TEST_OUTPUT})
file(COPY ${PROJECT_SOURCE_DIR}/tests/test_files DESTINATION ${TEST_OUTPUT})
