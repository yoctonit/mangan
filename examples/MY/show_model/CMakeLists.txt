add_executable(show_model
    main.cpp model_scene.cpp model_scene.h)

target_include_directories(show_model PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")

target_link_libraries(show_model mangan)

add_custom_command(
    TARGET show_model POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/diffuse.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/diffuse.vert)
add_custom_command(
    TARGET show_model POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/diffuse.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/diffuse.frag)
