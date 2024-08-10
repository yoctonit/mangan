# prepare shader files for chapter examples
file(COPY
        ../graphics/shader/BasicMaterial.vert
        ../graphics/shader/BasicMaterial.frag
        ../graphics/shader/TextureMaterial.vert
        ../graphics/shader/TextureMaterial.frag
        ../graphics/shader/FlatMaterial.vert
        ../graphics/shader/FlatMaterial.frag
        ../graphics/shader/LambertMaterial.vert
        ../graphics/shader/LambertMaterial.frag
        ../graphics/shader/PhongMaterial.vert
        ../graphics/shader/PhongMaterial.frag
        ../graphics/shader/Effect.vert
        ../graphics/shader/AdditiveBlendEffect.frag
        ../graphics/shader/BrightFilterEffect.frag
        ../graphics/shader/HorizontalBlurEffect.frag
        ../graphics/shader/VerticalBlurEffect.frag
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        ../images/grid.png
        ../images/brick-color.png
        ../images/brick-bump.png
        ../images/sky-earth.jpg
        ../images/grass.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

# Example 01
add_executable(dgf_test_6_01 test_6_01.cpp)
target_link_libraries(dgf_test_6_01 PRIVATE Mn::DGF)

# Example 02
add_executable(dgf_test_6_02 test_6_02.cpp)
target_link_libraries(dgf_test_6_02 PRIVATE Mn::DGF)

# Example 03
add_executable(dgf_test_6_03 test_6_03.cpp)
target_link_libraries(dgf_test_6_03 PRIVATE Mn::DGF)

# Example 04
add_executable(dgf_test_6_04 test_6_04.cpp)
target_link_libraries(dgf_test_6_04 PRIVATE Mn::DGF)
