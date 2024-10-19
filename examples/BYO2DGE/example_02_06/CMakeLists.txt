# prepare shader files for chapter examples
file(COPY
        shader/simple_vs.glsl
        shader/simple_fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

add_executable(byo2dge_ex_02_06 main.cpp src/Core.cpp)
target_link_libraries(byo2dge_ex_02_06 PRIVATE Mn::GL)
