# prepare shader files for chapter examples
file(COPY
        shader/colors.vs
        shader/colors.fs
        shader/light_cube.fs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

add_executable(joey-ex-1-1-colors ex-1-1-colors.cpp)
target_link_libraries(joey-ex-1-1-colors PRIVATE Mn::Engine PRIVATE Mn::Joey)
