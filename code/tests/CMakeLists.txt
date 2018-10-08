
set(ROOT "${PROJECT_SOURCE_DIR}/..")
function(add_test_exec file)
    add_executable(${file} ${file}.c)
    target_include_directories(${file} PUBLIC "${PROJECT_SOURCE_DIR}/src")
    target_link_libraries(${name} Back)
    set_target_properties(${file} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${ROOT}/build/tests"
    )
    add_test(NAME ${file} COMMAND ${file})
endfunction()

foreach(file IN ITEMS
    test_run
    )

    add_test_exec(${file})

endforeach()
