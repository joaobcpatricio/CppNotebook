set(APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

target_link_libraries(
        ${EXECUTABLE_NAME}
        PRIVATE ${SRC_NAME}
)