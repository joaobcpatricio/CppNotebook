find_package(Doxygen)

if (DOXYGEN_FOUND)
    add_custom_target(
            docs
            ${DOXYGEN_EXECUTABLE}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
    ) #This is just for defining an utility target where we can execute smthg on the terminal
endif ()