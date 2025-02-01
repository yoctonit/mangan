add_library(mngl
        window/Input.cpp window/Window.cpp window/Run.h
        core/Shader.cpp core/Vbo.cpp core/Ebo.cpp core/Vao.cpp
        core/Texture.cpp core/TextureCubeMap.cpp
        graphics/Attribute.cpp graphics/Uniform.cpp
        graphics/RenderSettings.cpp
        geometry/Geometry.cpp geometry/Box.cpp geometry/Icosahedron.cpp
        geometry/Surface.cpp geometry/Plane.cpp geometry/Polygon.cpp
        geometry/Rectangle.cpp geometry/Hexagon.cpp geometry/Ellipsoid.cpp
        geometry/Cylindrical.cpp geometry/Cylinder.cpp geometry/Cone.cpp
        geometry/Prism.cpp geometry/Pyramid.cpp geometry/Sphere.cpp
        graphics/ShaderInfo.cpp graphics/ShaderLoader.cpp graphics/Connection.cpp
        graphics/Buffer.cpp graphics/Mesh.cpp
)

target_link_libraries(mngl PRIVATE glfw)
target_link_libraries(mngl PUBLIC glad_4_3)
# files in graphics folder are dependent on glm and stb
# consider splitting engine library into components: core, ...
target_link_libraries(mngl PUBLIC glm::glm)
target_link_libraries(mngl PUBLIC nothings::stb)

target_include_directories(mngl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(Mn::GL ALIAS mngl)

add_executable(ref-cnt-test test/RefCntTest.cpp)
add_executable(math-test test/MathTest.cpp)
target_link_libraries(math-test PUBLIC Mn::GL)