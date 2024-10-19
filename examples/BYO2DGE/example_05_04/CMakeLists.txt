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

file(COPY
        assets/fonts/consolas-16.fnt
        assets/fonts/consolas-16.json
        assets/fonts/consolas-16.png
        assets/fonts/consolas-24.fnt
        assets/fonts/consolas-24.json
        assets/fonts/consolas-24.png
        assets/fonts/consolas-32.fnt
        assets/fonts/consolas-32.json
        assets/fonts/consolas-32.png
        assets/fonts/consolas-72.fnt
        assets/fonts/consolas-72.json
        assets/fonts/consolas-72.png
        assets/fonts/segment7-96.fnt
        assets/fonts/segment7-96.json
        assets/fonts/segment7-96.png
        assets/fonts/system_default_font.fnt
        assets/fonts/system_default_font.json
        assets/fonts/system_default_font.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fonts)

add_executable(byo2dge_ex_05_04 main.cpp
        src/Core.cpp src/Renderable.cpp src/TextureRenderable.cpp
        src/SpriteRenderable.cpp src/SpriteAnimateRenderable.cpp
        src/Font.cpp src/FontRenderable.cpp
        src/Transform.cpp src/Camera.cpp game/MyGame.cpp)
target_link_libraries(byo2dge_ex_05_04 PRIVATE Mn::GL)
