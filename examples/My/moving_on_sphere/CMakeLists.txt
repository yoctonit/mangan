file(COPY
        shader/basic.vs.glsl
        shader/basic.fs.glsl
        shader/ads.vs.glsl
        shader/ads.fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

add_executable(moving_on_sphere
        main.cpp
        Camera.cpp
        point_light.cpp
        Axes.cpp
        simple_spaceship.cpp
        Planet.cpp
        sphere_scene.cpp)
target_link_libraries(moving_on_sphere PRIVATE Mn::GL)

#add_custom_command(
#    TARGET moving_on_sphere POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vert
#    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vert)
#add_custom_command(
#    TARGET moving_on_sphere POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.frag
#    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.frag)
#add_custom_command(
#    TARGET moving_on_sphere POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    ${CMAKE_CURRENT_SOURCE_DIR}/shader/ads.vert
#    ${CMAKE_CURRENT_BINARY_DIR}/shader/ads.vert)
#add_custom_command(
#    TARGET moving_on_sphere POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    ${CMAKE_CURRENT_SOURCE_DIR}/shader/ads.frag
#    ${CMAKE_CURRENT_BINARY_DIR}/shader/ads.frag)
