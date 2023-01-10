add_executable(mandelbrot
    main.cpp mandelbrot_scene.cpp mandelbrot_scene.h)

target_link_libraries(mandelbrot mangan)

add_custom_command(
    TARGET mandelbrot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/mandelbrot.vert
    ${CMAKE_CURRENT_BINARY_DIR}/shader/mandelbrot.vert)
add_custom_command(
    TARGET mandelbrot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/mandelbrot.frag
    ${CMAKE_CURRENT_BINARY_DIR}/shader/mandelbrot.frag)
