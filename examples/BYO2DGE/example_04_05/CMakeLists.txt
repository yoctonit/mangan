# prepare shader files for chapter examples
file(COPY
        shader/simple_vs.glsl
        shader/simple_fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        assets/blue_level.json
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)

add_executable(byo2dge_ex_04_05 main.cpp
        src/Core.cpp src/Renderable.cpp src/Transform.cpp src/Camera.cpp
        game/SceneFileParser.cpp game/MyGame.cpp game/BlueLevel.cpp)
target_link_libraries(byo2dge_ex_04_05 PRIVATE Mn::Engine)
