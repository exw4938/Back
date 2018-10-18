include(CTest)

set(ROOT "${PROJECT_SOURCE_DIR}/..")
set(SRCS
    src/back.c
    src/config.c
    src/local.c
)

add_executable(back ${SRCS})
target_compile_options(back PRIVATE -ggdb -Wall -Wextra -pedantic)
add_library(source SHARED ${SRCS})
target_include_directories(source PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(back PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

set_target_properties(back source PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${ROOT}/build/src"
    RUNTIME_OUTPUT_DIRECTORY "${ROOT}/build/bin"
    INTERFACE_OUTPUT_DIRECTORY "${ROOT}/build/src"
)
