# prepare shader files for chapter examples
file(COPY
        shader/basic.vs
        shader/basic.fs
        shader/basic-yellow.fs
        shader/basic-color.fs
        shader/basic-pos-color-attr.vs
        shader/basic-pos-color-attr.fs
        shader/basic-pos-color-attr-upside-down.vs
        shader/basic-pos-color-attr-offset.vs
        shader/exercise-3-6.vs
        shader/exercise-3-6.fs
        shader/texture.vs
        shader/texture.fs
        shader/texture-combined.fs
        shader/exercise-4-3.fs
        shader/exercise-4-6.fs
        shader/transform.vs
        shader/transform.fs
        shader/coordinate-systems.vs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        ../images/container.jpg
        ../images/awesomeface.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

add_executable(joey-ex-2-1-triangle ex-2-1-triangle.cpp)
target_link_libraries(joey-ex-2-1-triangle PRIVATE Mn::Engine)

add_executable(joey-ex-2-1-triangle-refactored ex-2-1-triangle-refactored.cpp)
target_link_libraries(joey-ex-2-1-triangle-refactored PRIVATE Mn::Engine)

add_executable(joey-ex-2-2-triangle-indexed ex-2-2-triangle-indexed.cpp)
target_link_libraries(joey-ex-2-2-triangle-indexed PRIVATE Mn::Engine)

add_executable(joey-ex-2-2-triangle-indexed-refactored ex-2-2-triangle-indexed-refactored.cpp)
target_link_libraries(joey-ex-2-2-triangle-indexed-refactored PRIVATE Mn::Engine)

add_executable(joey-ex-2-3-triangle-exercise-1 ex-2-3-triangle-exercise-1.cpp)
target_link_libraries(joey-ex-2-3-triangle-exercise-1 PRIVATE Mn::Engine)

add_executable(joey-ex-2-4-triangle-exercise-2 ex-2-4-triangle-exercise-2.cpp)
target_link_libraries(joey-ex-2-4-triangle-exercise-2 PRIVATE Mn::Engine)

add_executable(joey-ex-2-5-triangle-exercise-3 ex-2-5-triangle-exercise-3.cpp)
target_link_libraries(joey-ex-2-5-triangle-exercise-3 PRIVATE Mn::Engine)

add_executable(joey-ex-3-1-shaders-uniform ex-3-1-shaders-uniform.cpp)
target_link_libraries(joey-ex-3-1-shaders-uniform PRIVATE Mn::Engine)

add_executable(joey-ex-3-2-shaders-interpolation ex-3-2-shaders-interpolation.cpp)
target_link_libraries(joey-ex-3-2-shaders-interpolation PRIVATE Mn::Engine)

add_executable(joey-ex-3-4-triangle-exercise-1 ex-3-4-triangle-exercise-1.cpp)
target_link_libraries(joey-ex-3-4-triangle-exercise-1 PRIVATE Mn::Engine)

add_executable(joey-ex-3-5-triangle-exercise-2 ex-3-5-triangle-exercise-2.cpp)
target_link_libraries(joey-ex-3-5-triangle-exercise-2 PRIVATE Mn::Engine)

add_executable(joey-ex-3-6-triangle-exercise-3 ex-3-6-triangle-exercise-3.cpp)
target_link_libraries(joey-ex-3-6-triangle-exercise-3 PRIVATE Mn::Engine)

add_executable(joey-ex-4-1-textures ex-4-1-textures.cpp)
target_link_libraries(joey-ex-4-1-textures PRIVATE Mn::Engine)

add_executable(joey-ex-4-2-textures-combined ex-4-2-textures-combined.cpp)
target_link_libraries(joey-ex-4-2-textures-combined PRIVATE Mn::Engine)

add_executable(joey-ex-4-3-textures-exercise-1 ex-4-3-textures-exercise-1.cpp)
target_link_libraries(joey-ex-4-3-textures-exercise-1 PRIVATE Mn::Engine)

add_executable(joey-ex-4-4-textures-exercise-2 ex-4-4-textures-exercise-2.cpp)
target_link_libraries(joey-ex-4-4-textures-exercise-2 PRIVATE Mn::Engine)

add_executable(joey-ex-4-5-textures-exercise-3 ex-4-5-textures-exercise-3.cpp)
target_link_libraries(joey-ex-4-5-textures-exercise-3 PRIVATE Mn::Engine)

add_executable(joey-ex-4-6-textures-exercise-4 ex-4-6-textures-exercise-4.cpp)
target_link_libraries(joey-ex-4-6-textures-exercise-4 PRIVATE Mn::Engine)

add_executable(joey-ex-5-1-transformations ex-5-1-transformations.cpp)
target_link_libraries(joey-ex-5-1-transformations PRIVATE Mn::Engine)

add_executable(joey-ex-5-2-transformations-exercise-1 ex-5-2-transformations-exercise-1.cpp)
target_link_libraries(joey-ex-5-2-transformations-exercise-1 PRIVATE Mn::Engine)

add_executable(joey-ex-5-3-transformations-exercise-2 ex-5-3-transformations-exercise-2.cpp)
target_link_libraries(joey-ex-5-3-transformations-exercise-2 PRIVATE Mn::Engine)

add_executable(joey-ex-6-1-coordinate-systems ex-6-1-coordinate-systems.cpp)
target_link_libraries(joey-ex-6-1-coordinate-systems PRIVATE Mn::Engine)

add_executable(joey-ex-6-2-coordinate-systems-depth ex-6-2-coordinate-systems-depth.cpp)
target_link_libraries(joey-ex-6-2-coordinate-systems-depth PRIVATE Mn::Engine)

add_executable(joey-ex-6-3-coordinate-systems-multiple ex-6-3-coordinate-systems-multiple.cpp)
target_link_libraries(joey-ex-6-3-coordinate-systems-multiple PRIVATE Mn::Engine)

add_executable(joey-ex-6-4-coordinate-systems-exercise-3 ex-6-4-coordinate-systems-exercise-3.cpp)
target_link_libraries(joey-ex-6-4-coordinate-systems-exercise-3 PRIVATE Mn::Engine)

add_executable(joey-ex-7-1-camera-circle ex-7-1-camera-circle.cpp)
target_link_libraries(joey-ex-7-1-camera-circle PRIVATE Mn::Engine)

add_executable(joey-ex-7-2-camera-walk ex-7-2-camera-walk.cpp)
target_link_libraries(joey-ex-7-2-camera-walk PRIVATE Mn::Engine)

add_executable(joey-ex-7-3-camera-zoom ex-7-3-camera-zoom.cpp)
target_link_libraries(joey-ex-7-3-camera-zoom PRIVATE Mn::Engine)
