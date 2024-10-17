set(LIBRARY_SOURCES example_class.cpp)
set(LIBRARY_HEADERS example_class.hpp)
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(${SRC_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${SRC_NAME} PUBLIC ${LIBRARY_INCLUDES})

