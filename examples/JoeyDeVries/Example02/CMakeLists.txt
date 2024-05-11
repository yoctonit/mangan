add_executable(joey-example02 main.cpp)
target_link_libraries(joey-example02 PRIVATE wnd core)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/basic.vs
        ${CMAKE_CURRENT_BINARY_DIR}/basic.vs
        COPYONLY
)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/basic.fs
        ${CMAKE_CURRENT_BINARY_DIR}/basic.fs
        COPYONLY
)
