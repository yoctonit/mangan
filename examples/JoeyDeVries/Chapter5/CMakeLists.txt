# prepare shader files for chapter examples
file(COPY
        shader/blinn.vs.glsl
        shader/blinn.fs.glsl
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        ../images/wood.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

add_executable(joey-ex-5-1-blinn-lighting ex-5-1-blinn.cpp)
target_link_libraries(joey-ex-5-1-blinn-lighting PRIVATE Mn::GL PRIVATE Mn::Joey)
