function(parse_test_file)
    set(one_value_args FILENAME)
    set(multi_value_args INCLUDES LIBRARIES)
    cmake_parse_arguments(PARSE_TEST "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

    if(EXISTS ${PARSE_TEST_FILENAME})
        # Get file name without directories and extension.
        get_filename_component(test_file_no_ext ${PARSE_TEST_FILENAME} NAME_WE)
        add_executable(${test_file_no_ext} "${PARSE_TEST_FILENAME}")
        target_include_directories(${test_file_no_ext} PUBLIC "${PARSE_TEST_INCLUDES}")
        target_link_libraries(${test_file_no_ext} PUBLIC "${PARSE_TEST_LIBRARIES}")

        file(READ ${PARSE_TEST_FILENAME} file_contents)
        string(REGEX MATCHALL "TEST\\([A-Za-z0-9_]*\\)" regex_result ${file_contents}) # Parse out full test contents for the function

        foreach(test_match ${regex_result}) # Extract just the test name portion
            string(REGEX REPLACE "TEST\\(([A-Za-z0-9_]*)\\)" "\\1" actual_test_name ${test_match})
            add_test(NAME "${test_file_no_ext}_${actual_test_name}" COMMAND ${test_file_no_ext} ${actual_test_name})
        endforeach()
        
    endif()
endfunction()
