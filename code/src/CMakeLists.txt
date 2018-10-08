
set(ROOT "${PROJECT_SOURCE_DIR}/..")
set(SRCS
    back.c
    config.c
)

add_executable(back ${SRCS})
add_library(Back STATIC ${SRCS})

set_target_properties(back Back PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${ROOT}/build/src"
    RUNTIME_OUTPUT_DIRECTORY "${ROOT}/build/bin"
)


target_include_directories(back PUBLIC /build/src)
