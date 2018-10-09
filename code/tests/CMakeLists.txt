
include(CTest)
set(ROOT "${PROJECT_SOURCE_DIR}/..")
function(add_test_exec name)
    add_executable(${name} src/${name}.c)
    target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include")
    target_link_libraries(${name} source)
    set_target_properties(${name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${ROOT}/build/tests"
    )
    add_test(NAME ${name} COMMAND "${ROOT}/build/tests/${name}")
endfunction()

foreach(name IN ITEMS
    test_config
    )

    add_test_exec(${name})

endforeach()
