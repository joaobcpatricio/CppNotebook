cmake_minimum_required(VERSION 3.22)

#Indicate project name, version, and languages
project(
        CppProjectTemplate
        VERSION 1.0.0
        LANGUAGES C CXX)

#Set settings for C++
set(CMAKE_CXX_STANDARD 20) #sets the default standard to C++ 20
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) #Does not allow to use features outside the standard C++

#CPM
option(USE_CPM "Whether to use CPM" ON)

#Tests
option(ENABLE_TESTING "Enable a Unit Testing Build" ON)

#Clang tidy
option(ENABLE_CLANG_TIDY "Enable to add clang tidy." ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")


if (USE_CPM)
    message(STATUS "Using CPM")
    include(CPM)
    cpmaddpackage("gh:catchorg/Catch2#v2.13.9")
else ()
    message(STATUS "Using FetchContent")
    #add cmake libraries on a different way than the submodules than previously   

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2
            GIT_TAG v2.13.9
            GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(Catch2)
endif ()

#add_subdirectory(configured)
#add_subdirectory(external)
add_subdirectory(src) #should be first as it is the library
#add_subdirectory(app)
add_subdirectory(tests)

