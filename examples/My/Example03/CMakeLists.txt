file(COPY
        basic.vs.glsl
        basic.fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

add_executable(example03 main.cpp)
target_link_libraries(example03 PRIVATE Mn::GL)
