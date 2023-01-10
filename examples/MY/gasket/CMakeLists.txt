add_executable(gasket
    main.cpp gasket_scene.cpp gasket_scene.h)

target_link_libraries(gasket mangan)

add_custom_command(
    TARGET gasket POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vert)
add_custom_command(
    TARGET gasket POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.frag)
