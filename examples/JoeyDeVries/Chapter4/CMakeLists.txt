# prepare shader files for chapter examples
file(COPY
        shader/depth_testing.vs
        shader/depth_testing.fs
        shader/depth_testing_view.vs
        shader/depth_testing_view.fs
        shader/stencil_testing.vs
        shader/stencil_testing.fs
        shader/stencil_single_color.vs
        shader/stencil_single_color.fs
        shader/blending.vs
        shader/blending_discard.fs
        shader/blending.fs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        ../images/grass.png
        ../images/marble.jpg
        ../images/metal.png
        ../images/window.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

add_executable(joey-ex-1-1-depth-testing ex-1-1-depth-testing.cpp)
target_link_libraries(joey-ex-1-1-depth-testing PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-1-2-depth-testing-view ex-1-2-depth-testing-view.cpp)
target_link_libraries(joey-ex-1-2-depth-testing-view PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-2-1-stencil-testing ex-2-1-stencil-testing.cpp)
target_link_libraries(joey-ex-2-1-stencil-testing PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-3-1-blending-discard ex-3-1-blending-discard.cpp)
target_link_libraries(joey-ex-3-1-blending-discard PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-3-2-blending ex-3-2-blending.cpp)
target_link_libraries(joey-ex-3-2-blending PRIVATE Mn::Engine PRIVATE Mn::Joey)
