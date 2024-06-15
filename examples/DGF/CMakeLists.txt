add_library(dgf_lib
        graphics/core/Base.cpp
        graphics/core/Input.cpp
        graphics/core/Shader.cpp
        graphics/core/Attribute.cpp
        graphics/core/Uniform.cpp)
target_link_libraries(dgf_lib PRIVATE glfw)
target_link_libraries(dgf_lib PUBLIC glad_4_3)

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
# add_subdirectory(Chapter3)
#add_subdirectory(Chapter4)
