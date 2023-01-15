add_library(mngl
        src/Window.h src/Window.cpp
        src/Input.h src/Input.cpp
        src/Run.h
        src/Util.h
        src/Shader.h src/Shader.cpp
        src/Uniform.h
        src/Attribute.h
        src/dgf/Object3D.h
        src/dgf/Scene.h
        src/dgf/Group.h
        src/dgf/Camera.h
        src/dgf/geometry/Geometry.h
        src/dgf/geometry/Rectangle.h
        src/dgf/geometry/Box.h
        src/dgf/geometry/Polygon.h
        src/dgf/geometry/Surface.h
        src/dgf/geometry/Axes.h
        src/dgf/geometry/MovementRig.h
        src/dgf/RenderSetting.h
        src/dgf/Renderer.h
        src/dgf/material/Material.h
        src/dgf/material/BasicMaterial.h
        src/dgf/material/LineMaterial.h
        src/dgf/material/PointMaterial.h
        src/dgf/material/SurfaceMaterial.h
        src/dgf/Mesh.h
        src/dgf/Texture.h
        )
#target_link_libraries(glwnd OpenGL::GL) # alternatively: add_dependencies(mangan OpenGL::GL)
target_link_libraries(mngl PUBLIC glfw)
target_link_libraries(mngl PUBLIC glad_4_3)
target_include_directories(mngl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(mngl PUBLIC "${CMAKE_SOURCE_DIR}/deps/glm.0.9.9.7")
target_include_directories(mngl PUBLIC "${CMAKE_SOURCE_DIR}/deps/stb")
