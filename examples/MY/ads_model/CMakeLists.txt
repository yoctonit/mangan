add_executable(ads_model
    main.cpp ads_scene.cpp ads_scene.h
    ads_renderer.cpp ads_renderer.h)

target_include_directories(ads_model PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")

target_link_libraries(ads_model mangan)

add_custom_command(
    TARGET ads_model POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/ads.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/ads.vert)
add_custom_command(
    TARGET ads_model POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/ads.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/ads.frag)
