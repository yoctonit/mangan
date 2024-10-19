# prepare shader files for chapter examples
file(COPY
        shader/simple_vs.glsl
        shader/simple_fs.glsl
        shader/texture_vs.glsl
        shader/texture_fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        assets/minion_sprite.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)

file(COPY
        assets/fonts/system_default_font.fnt
        assets/fonts/system_default_font.json
        assets/fonts/system_default_font.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fonts)

add_executable(byo2dge_ex_06_02 main.cpp
        src/Core.cpp src/Renderable.cpp src/TextureRenderable.cpp
        src/SpriteRenderable.cpp src/SpriteAnimateRenderable.cpp
        src/Font.cpp src/FontRenderable.cpp
        src/Transform.cpp src/Camera.cpp game/MyGame.cpp)
target_link_libraries(byo2dge_ex_06_02 PRIVATE Mn::GL)
