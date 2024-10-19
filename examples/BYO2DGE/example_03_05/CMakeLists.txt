# prepare shader files for chapter examples
file(COPY
        shader/simple_vs.glsl
        shader/simple_fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

add_executable(byo2dge_ex_03_05 main.cpp
        src/Core.cpp src/Renderable.cpp src/Transform.cpp src/Camera.cpp)
target_link_libraries(byo2dge_ex_03_05 PRIVATE Mn::GL)
