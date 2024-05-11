add_library(core src/Shader.cpp src/Buffer.cpp src/ElementBuffer.cpp src/Vao.cpp)

target_link_libraries(core PRIVATE glad_4_3)

target_include_directories(core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(core PUBLIC "${CMAKE_SOURCE_DIR}/deps/glm.0.9.9.7")

add_library(Mn::Core ALIAS core)
