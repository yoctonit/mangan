add_library(engine
        engine/Input.cpp engine/Window.cpp engine/Run.h
        graphics/Shader.cpp graphics/Vbo.cpp
        graphics/Vao.cpp graphics/Ebo.cpp
        graphics/Uniform.cpp graphics/Texture.cpp
        geometry/Icosahedron.cpp
)

target_link_libraries(engine PRIVATE glfw)
target_link_libraries(engine PUBLIC glad_4_3)
# in files in graphics folder are dependent on glm and stb
# consider splitting engine library into components: core, ...
target_link_libraries(engine PUBLIC glm::glm)
target_link_libraries(engine PUBLIC nothings::stb)

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(Mn::Engine ALIAS engine)

#add_library(engine engine/Action.cpp engine/Engine.cpp engine/Input.cpp engine/Scene.cpp engine/vec2.cpp engine/Window.cpp)
