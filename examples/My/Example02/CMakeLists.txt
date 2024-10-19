file(COPY
        basic.vs.glsl
        basic.fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

add_executable(example02 main.cpp)
target_link_libraries(example02 PRIVATE Mn::GL)
