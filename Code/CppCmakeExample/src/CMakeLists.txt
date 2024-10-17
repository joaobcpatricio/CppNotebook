# Add all sources here
set(LIBRARY_NAME example_class) #indicate variable names by upper case


set(LIBRARY_SOURCES example_class.cpp)
set(LIBRARY_HEADERS example_class.h)
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})

