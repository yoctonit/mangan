add_library(mngl
        src/Window.h src/Window.cpp
        src/Input.h src/Input.cpp
        src/Run.h
        src/Util.h
        src/Shader.h src/Shader.cpp
        src/Uniform.h
        src/Attribute.h
        src/Object3D.h
        src/Scene.h
        src/Group.h
        src/Camera.h
        src/geometry/Geometry.h
        src/geometry/Rectangle.h
        src/geometry/Box.h
        src/geometry/Polygon.h
        src/geometry/Surface.h
        src/RenderSetting.h
        src/Renderer.h
        src/material/Material.h
        src/material/BasicMaterial.h
        src/material/LineMaterial.h
        src/material/PointMaterial.h
        src/material/SurfaceMaterial.h
        src/Mesh.h
        )
#target_link_libraries(glwnd OpenGL::GL) # alternatively: add_dependencies(mangan OpenGL::GL)
target_link_libraries(mngl PUBLIC glfw)
target_link_libraries(mngl PUBLIC glad_4_3)
target_include_directories(mngl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(mngl PUBLIC "${CMAKE_SOURCE_DIR}/deps/glm.0.9.9.7")
