add_library(mngl
        src/Window.h src/Window.cpp
        src/Input.h src/Input.cpp
        src/Run.h
        src/Util.h src/Util.cpp
        src/Shader.h src/Shader.cpp
        src/Texture.h
        src/byo2dge/shader/ShaderInterface.h
        src/byo2dge/shader/SimpleShader.h
        src/byo2dge/shader/TextureShader.h
        src/byo2dge/shader/SpriteShader.h
        src/byo2dge/SquareGeometryBuffer.h
        src/byo2dge/CharacterInfo.h
        src/byo2dge/renderable/Renderable.h
        src/byo2dge/renderable/TextureRenderable.h
        src/byo2dge/renderable/SpriteRenderable.h
        src/byo2dge/renderable/SpriteAnimateRenderable.h
        src/byo2dge/renderable/FontRenderable.h
        src/byo2dge/Transform.h src/byo2dge/Camera.h
        src/byo2dge/Engine.h src/byo2dge/SceneFileParser.h
        src/byo2dge/BoundingBox.h
        src/byo2dge/game_objects/GameObject.h
        src/byo2dge/game_objects/GameObjectSet.h
        src/byo2dge/Lerp.h
        src/byo2dge/Oscilate.h
        )
#target_link_libraries(glwnd OpenGL::GL) # alternatively: add_dependencies(mangan OpenGL::GL)
target_link_libraries(mngl PUBLIC glfw)
target_link_libraries(mngl PUBLIC glad_4_3)
target_include_directories(mngl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(mngl PUBLIC "${CMAKE_SOURCE_DIR}/deps/glm.0.9.9.7")
target_include_directories(mngl PUBLIC "${CMAKE_SOURCE_DIR}/deps/stb")
target_include_directories(mngl PUBLIC "${CMAKE_SOURCE_DIR}/deps/nlohmann")

#add_library(mngl
#        src/Window.h src/Window.cpp
#        src/Input.h src/Input.cpp
#        src/Run.h
#        src/Util.h
#        src/Shader.h src/Shader.cpp
#        src/Uniform.h
#        src/Attribute.h
#        src/dgf/Object3D.h
#        src/dgf/Scene.h
#        src/dgf/Group.h
#        src/dgf/Camera.h
#        src/dgf/geometry/Geometry.h
#        src/dgf/geometry/Rectangle.h
#        src/dgf/geometry/Box.h
#        src/dgf/geometry/Polygon.h
#        src/dgf/geometry/Surface.h
#        src/dgf/geometry/Axes.h
#        src/dgf/geometry/MovementRig.h
#        src/dgf/RenderSetting.h
#        src/dgf/Renderer.h
#        src/dgf/material/Material.h
#        src/dgf/material/BasicMaterial.h
#        src/dgf/material/LineMaterial.h
#        src/dgf/material/PointMaterial.h
#        src/dgf/material/SurfaceMaterial.h
#        src/dgf/material/SpriteMaterial.h
#        src/dgf/Mesh.h
#        src/dgf/Texture.h
#        src/dgf/RenderTarget.h
#        src/dgf/material/TextureMaterial.h)
