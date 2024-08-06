# prepare shader files for chapter examples
file(COPY
        ../graphics/shader/FlatMaterial.vert
        ../graphics/shader/FlatMaterial.frag
        ../graphics/shader/LambertMaterial.vert
        ../graphics/shader/LambertMaterial.frag
        ../graphics/shader/PhongMaterial.vert
        ../graphics/shader/PhongMaterial.frag
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        ../images/grid.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

# Example 01
add_executable(dgf_test_6_01 test_6_01.cpp)
target_link_libraries(dgf_test_6_01 PRIVATE Mn::DGF)
