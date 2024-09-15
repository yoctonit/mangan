# prepare shader files for chapter examples
file(COPY
        shader/depth_testing.vs
        shader/depth_testing.fs
        shader/depth_testing_view.vs
        shader/depth_testing_view.fs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        ../images/marble.jpg
        ../images/metal.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

add_executable(joey-ex-1-1-depth-testing ex-1-1-depth-testing.cpp)
target_link_libraries(joey-ex-1-1-depth-testing PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-1-2-depth-testing-view ex-1-2-depth-testing-view.cpp)
target_link_libraries(joey-ex-1-2-depth-testing-view PRIVATE Mn::Engine PRIVATE Mn::Joey)
