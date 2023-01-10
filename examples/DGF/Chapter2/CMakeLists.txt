add_executable(empty e01_empty.cpp)
target_link_libraries(empty mangan1)

add_executable(point e02_point.cpp)
target_link_libraries(point mangan1)

add_executable(shape e03_shape.cpp)
target_link_libraries(shape mangan1)

add_executable(shape2 e04_shape.cpp)
target_link_libraries(shape2 mangan1)

add_executable(shape3 e05_shape.cpp)
target_link_libraries(shape3 mangan1)

add_executable(shape4 e06_shape.cpp)
target_link_libraries(shape4 mangan1)

add_executable(shape5 e07_shape.cpp)
target_link_libraries(shape5 mangan1)

add_executable(shape6 e08_shape.cpp)
target_link_libraries(shape6 mangan1)

add_executable(shape7 e09_shape.cpp)
target_link_libraries(shape7 mangan1)

add_custom_command(
    TARGET point POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/point.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/point.vert)
add_custom_command(
    TARGET point POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/point.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/point.frag)
add_custom_command(
    TARGET shape POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/shape.vert
    ${CMAKE_CURRENT_BIN_colARY_DIR}/shader/shape.vert)
add_custom_command(
    TARGET shape POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/shape.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/shape.frag)
add_custom_command(
    TARGET shape3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/shape_col.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/shape_col.vert)
add_custom_command(
    TARGET shape3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/shape_col.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/shape_col.frag)
add_custom_command(
    TARGET shape4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/shape_translation.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/shape_translation.vert)
add_custom_command(
    TARGET shape4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/shape_translation.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/shape_translation.frag)
