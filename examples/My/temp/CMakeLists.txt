add_executable(main main.cpp)
target_link_libraries(main PUBLIC mngl)

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vs)
add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.fs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.fs)
