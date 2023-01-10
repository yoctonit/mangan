add_executable(triangle
    main.cpp triangle_scene.cpp triangle_scene.h)

target_link_libraries(triangle mangan)

add_custom_command(
    TARGET triangle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vert)
add_custom_command(
    TARGET triangle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.frag)
