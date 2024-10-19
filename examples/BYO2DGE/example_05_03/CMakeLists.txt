# prepare shader files for chapter examples
file(COPY
        shader/simple_vs.glsl
        shader/simple_fs.glsl
        shader/texture_vs.glsl
        shader/texture_fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        assets/consolas-72.png
        assets/minion_sprite.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)

add_executable(byo2dge_ex_05_03 main.cpp
        src/Core.cpp src/Renderable.cpp src/TextureRenderable.cpp
        src/SpriteRenderable.cpp src/SpriteAnimateRenderable.cpp
        src/Transform.cpp src/Camera.cpp game/MyGame.cpp)
target_link_libraries(byo2dge_ex_05_03 PRIVATE Mn::GL)
