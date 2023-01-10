add_executable(free_type_test main.cpp)

target_include_directories(free_type_test PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")

target_link_libraries(free_type_test PRIVATE mangan)
target_link_libraries(free_type_test PRIVATE freetype)

add_custom_command(
    TARGET free_type_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/vertex.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/shader/vertex.glsl)
add_custom_command(
    TARGET free_type_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/fragment.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/shader/fragment.glsl)
add_custom_command(
    TARGET free_type_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/fonts/LinLibertine_R.ttf
    ${CMAKE_CURRENT_BINARY_DIR}/fonts/LinLibertine_R.ttf)
