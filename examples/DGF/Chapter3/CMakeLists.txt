add_executable(triangle3d e01_triangle.cpp)
target_link_libraries(triangle3d mangan1)
target_include_directories(triangle3d PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")

add_custom_command(
    TARGET triangle3d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/shape3d.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/shape3d.vert)
add_custom_command(
    TARGET triangle3d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/shape3d.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/shape3d.frag)
