add_executable(moving_in_plane main.cpp
    simple_spaceship.cpp simple_spaceship.h
    ground.cpp ground.h
    plane_scene.cpp plane_scene.h)

target_link_libraries(moving_in_plane PRIVATE mangan)

target_include_directories(moving_in_plane PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")

add_custom_command(
    TARGET moving_in_plane POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vert)
add_custom_command(
    TARGET moving_in_plane POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.frag)
