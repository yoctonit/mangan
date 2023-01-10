add_executable(tetris main.cpp
    game_grid.cpp game_grid.h
    tetronimo.cpp tetronimo.h)

target_include_directories(tetris PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")
target_link_libraries(tetris PRIVATE mangan)

add_custom_command(
    TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vert)
add_custom_command(
    TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.frag)
