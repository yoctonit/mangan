# prepare shader files for chapter examples
file(COPY
        ../graphics/shader/TextureMaterial.vert
        ../graphics/shader/TextureMaterial.frag
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        images/grid.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

# Example 01
add_executable(dgf_test_5_01 test_5_01.cpp)
target_link_libraries(dgf_test_5_01 PRIVATE Mn::DGF)
