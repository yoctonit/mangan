# prepare shader files for chapter examples
file(COPY
        shader/simple_vs.glsl
        shader/simple_fs.glsl
        shader/texture_vs.glsl
        shader/texture_fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        assets/blue_level.json
        assets/minion_collector.jpg
        assets/minion_collector.png
        assets/minion_portal.jpg
        assets/minion_portal.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)

add_executable(byo2dge_ex_05_01 main.cpp
        src/Core.cpp src/Renderable.cpp src/TextureRenderable.cpp
        src/Transform.cpp src/Camera.cpp
        game/SceneFileParser.cpp game/MyGame.cpp game/BlueLevel.cpp)
target_link_libraries(byo2dge_ex_05_01 PRIVATE Mn::GL)
