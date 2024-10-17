if (ENABLE_TESTING)
    set(TEST_MAIN "unit_tests")
    set(TEST_SOURCES "test_example.cpp")
    set(TEST_INCLUDES "./")

    add_executable(${TEST_MAIN} ${TEST_SOURCES})
    target_include_directories(${TEST_MAIN} PUBLIC ${TEST_INCLUDES}) #For files used under tests
    target_link_libraries(${TEST_MAIN} PUBLIC
        example_class
            Catch2::Catch2)
endif ()