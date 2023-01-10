# we have three dependencies: OpenGL, GLFW and glad

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

# include GLFW project
# but don't build the GLFW tests, examples and documentation.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/glfw-3.3.2)

# include glad extension loading library
add_subdirectory(deps/glad4.6)

# our library
add_library(mangan
    src/core/util/text_file_loader.cpp src/core/util/text_file_loader.h
    src/core/shader/shader_compiler.cpp src/core/shader/shader_compiler.h
    src/core/shader/program_linker.cpp src/core/shader/program_linker.h
    src/core/shader/program_parser.cpp src/core/shader/program_parser.h
    src/core/shader/shader_program.cpp src/core/shader/shader_program.h
    src/core/shader/program_library.cpp src/core/shader/program_library.h
    src/core/buffer/gpu_buffer.cpp src/core/buffer/gpu_buffer.h
    src/core/buffer/buffer_library.cpp src/core/buffer/buffer_library.h
    src/core/buffer/vao_library.cpp src/core/buffer/vao_library.h
    src/core/window/gl_window.cpp src/core/window/gl_window.h
    src/core/window/input.cpp src/core/window/input.h
    src/core/window/scene.h
    src/camera/orthographic_camera.cpp src/camera/orthographic_camera.h
    src/camera/perspective_camera.cpp src/camera/perspective_camera.cpp
    src/light/point_light.cpp src/light/point_light.h
    src/model/model.h
    src/model/icosahedron.cpp src/model/icosahedron.h
    src/model/vertex_normal_model.h
    src/util/canvas.cpp src/util/canvas.h
    src/renderer/ads_renderer.cpp src/renderer/ads_renderer.h
    src/renderer/icosahedron_renderer.cpp src/renderer/icosahedron_renderer.h)

target_include_directories(mangan PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(mangan PRIVATE "${CMAKE_SOURCE_DIR}/glm.0.9.9.7")

target_link_libraries(mangan OpenGL::GL) # alternatively: add_dependencies(mangan OpenGL::GL)
target_link_libraries(mangan glfw)
target_link_libraries(mangan glad_4_6)

add_library(mangan1
    src/core/window.h src/core/window.cpp
    src/core/input.h src/core/input.cpp
    src/core/run.h
    src/core/shader.h src/core/shader.cpp
    src/core/attribute.h src/core/attribute.cpp
    src/core/uniform.h src/core/uniform.cpp
    src/core/util.h src/core/util.cpp
    src/core/buffer/gpu_buffer.cpp src/core/buffer/gpu_buffer.h
    )
target_include_directories(mangan1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(mangan1 OpenGL::GL)
target_link_libraries(mangan1 glfw)
target_link_libraries(mangan1 glad_4_6)
