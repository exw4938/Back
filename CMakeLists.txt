cmake_minimum_required (VERSION 2.6)
project (back)

set(back_VERSION_MAJOR 0)
set(back_VERSION_MINOR 1)

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()

configure_file (
    "${PROJECT_SOURCE_DIR}/src/cmake/backConfig.h.in"
    "${PROJECT_BINARY_DIR}/backConfig.h"
)

set(SRCS
    src/back.c
    src/config.c
)


file(COPY ${PROJECT_SOURCE_DIR}/config DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include_directories("${PROJECT_BINARY_DIR}")

add_executable(back ${SRCS})

#add_custom_command(TARGET back PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_COMMAND}/config ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
