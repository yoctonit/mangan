file(COPY
        shader/basic.vs.glsl
        shader/basic.fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

add_executable(example04 main.cpp Camera.cpp)
target_link_libraries(example04 PRIVATE Mn::GL)
