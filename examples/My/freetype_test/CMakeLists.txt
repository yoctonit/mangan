file(COPY
        shader/vertex.glsl
        shader/fragment.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        fonts/LinLibertine_R.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fonts)

add_executable(free_type_test main.cpp)
target_link_libraries(free_type_test PRIVATE Mn::GL PRIVATE freetype)
