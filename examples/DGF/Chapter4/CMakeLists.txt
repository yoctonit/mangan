add_executable(scene3d e01_shape.cpp)
target_link_libraries(scene3d PUBLIC dgf)
target_link_libraries(scene3d PUBLIC mnglwnd)
target_link_libraries(scene3d PUBLIC mngl)

# target_include_directories(scene3d PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")

add_custom_command(
    TARGET scene3d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/BasicMaterial.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/BasicMaterial.vert)
add_custom_command(
    TARGET scene3d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/BasicMaterial.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/BasicMaterial.frag)
