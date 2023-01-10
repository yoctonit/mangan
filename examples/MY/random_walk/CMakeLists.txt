add_executable(random_walk main.cpp bitmap_scene.cpp bitmap_scene.h)

target_include_directories(random_walk PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")
target_link_libraries(random_walk mangan)

add_custom_command(
    TARGET random_walk POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vert)
add_custom_command(
    TARGET random_walk POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.frag)
