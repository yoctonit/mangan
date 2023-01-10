add_executable(colored_square
    main.cpp colored_square_scene.cpp colored_square_scene.h
    colored_square.cpp colored_square.h
    player.cpp player.h
    colored_square_renderer.cpp colored_square_renderer.h)

target_include_directories(colored_square PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")

target_link_libraries(colored_square mangan)

add_custom_command(
    TARGET colored_square POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vert)
add_custom_command(
    TARGET colored_square POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.frag)
