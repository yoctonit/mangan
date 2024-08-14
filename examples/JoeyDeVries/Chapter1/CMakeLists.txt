# prepare shader files for chapter examples
file(COPY
        shader/basic.vs
        shader/basic.fs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)


add_executable(joey-ex-2-1-triangle ex-2-1-triangle.cpp)
target_link_libraries(joey-ex-2-1-triangle PRIVATE Mn::Engine)

add_executable(joey-ex-2-1-triangle-refactored ex-2-1-triangle-refactored.cpp)
target_link_libraries(joey-ex-2-1-triangle-refactored PRIVATE Mn::Engine)
