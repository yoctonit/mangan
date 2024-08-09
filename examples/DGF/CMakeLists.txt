add_library(dgf_lib
        graphics/core/Base.cpp
        graphics/core/Input.cpp
        graphics/core/Shader.cpp
        graphics/core/Attribute.cpp
        graphics/core/Uniform.cpp
        graphics/core/Texture.cpp
        graphics/core/Object3D.cpp
        graphics/core/Mesh.cpp
        graphics/core/Group.cpp
        graphics/core/Scene.cpp
        graphics/core/Camera.cpp
        graphics/core/Renderer.cpp
        graphics/core/RenderTarget.cpp
        graphics/core/RenderSettings.cpp
        graphics/geometry/Geometry.cpp
        graphics/geometry/BoxGeometry.cpp
        graphics/geometry/RectangleGeometry.cpp
        graphics/geometry/PolygonGeometry.cpp
        graphics/geometry/SurfaceGeometry.cpp
        graphics/geometry/HexagonGeometry.cpp
        graphics/geometry/PlaneGeometry.cpp
        graphics/geometry/EllipsoidGeometry.cpp
        graphics/geometry/SphereGeometry.cpp
        graphics/geometry/CylindricalGeometry.cpp
        graphics/geometry/ConeGeometry.cpp
        graphics/geometry/CylinderGeometry.cpp
        graphics/geometry/PrismGeometry.cpp
        graphics/geometry/PyramidGeometry.cpp
        graphics/extras/AxesGeometry.cpp
        graphics/extras/AxesHelper.cpp
        graphics/extras/GridGeometry.cpp
        graphics/extras/GridHelper.cpp
        graphics/extras/MovementRig.cpp
        graphics/extras/DirectionalLightHelper.cpp
        graphics/extras/PointLightHelper.cpp
        graphics/extras/Postprocessor.cpp
        graphics/light/Light.cpp
        graphics/light/AmbientLight.cpp
        graphics/light/DirectionalLight.cpp
        graphics/light/PointLight.cpp
        graphics/material/Material.cpp
        graphics/material/BasicMaterial.cpp
        graphics/material/LineMaterial.cpp
        graphics/material/PointMaterial.cpp
        graphics/material/SurfaceMaterial.cpp
        graphics/material/TextureMaterial.cpp
        graphics/material/SpriteMaterial.cpp
        graphics/material/FlatMaterial.cpp
        graphics/material/LambertMaterial.cpp
        graphics/material/PhongMaterial.cpp
        graphics/effects/Effect.cpp
        graphics/effects/AdditiveBlendEffect.cpp
        graphics/effects/BrightFilterEffect.cpp
        graphics/effects/ColorReduceEffect.cpp
        graphics/effects/HorizontalBlurEffect.cpp
        graphics/effects/InvertEffect.cpp
        graphics/effects/PixelateEffect.cpp
        graphics/effects/TintEffect.cpp
        graphics/effects/VerticalBlurEffect.cpp
        graphics/effects/VignetteEffect.cpp)
target_link_libraries(dgf_lib PRIVATE glfw)
target_link_libraries(dgf_lib PUBLIC glad_4_3)
target_link_libraries(dgf_lib PUBLIC glm::glm)
target_link_libraries(dgf_lib PUBLIC nothings::stb)

target_include_directories(dgf_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/graphics")

add_library(Mn::DGF ALIAS dgf_lib)

# add_library(dfgbook
#     core/openGLUtils.h core/openGLUtils.cpp
#     core/Object3D.h
#     core/Scene.h
#     core/Group.h
#     core/Camera.h
#     core/Geometry.h
#     core/RectangleGeometry.h
#     core/RenderSetting.h
#     core/Material.h
#     core/Mesh.h)
# set_target_properties(dfgbook PROPERTIES LINKER_LANGUAGE CXX)
# #target_link_libraries(dfgbook PUBLIC mangan1)
# target_include_directories(dfgbook PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/core")
# target_include_directories(dfgbook PUBLIC "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")
#target_link_libraries(dfg OpenGL::GL)
#target_link_libraries(dfg glfw)
#target_link_libraries(dfg glad_4_6)


add_subdirectory(Chapter2)
add_subdirectory(Chapter3)
add_subdirectory(Chapter4)
add_subdirectory(Chapter5)
add_subdirectory(Chapter6)
