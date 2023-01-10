add_executable(moving_on_sphere main.cpp
    simple_spaceship.cpp simple_spaceship.h
    planet_renderer.cpp planet_renderer.h
    sphere_scene.cpp sphere_scene.h)

target_link_libraries(moving_on_sphere PRIVATE mangan)

target_include_directories(moving_on_sphere PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")

add_custom_command(
    TARGET moving_on_sphere POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vert)
add_custom_command(
    TARGET moving_on_sphere POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.frag)
add_custom_command(
    TARGET moving_on_sphere POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/ads.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/ads.vert)
add_custom_command(
    TARGET moving_on_sphere POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/ads.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/ads.frag)
