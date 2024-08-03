# prepare shader files for chapter examples
#file(COPY
#        ../graphics/shader/BasicMaterial.vert
#        ../graphics/shader/BasicMaterial.frag
#        ../graphics/shader/TextureMaterial.vert
#        ../graphics/shader/TextureMaterial.frag
#        ../graphics/shader/SpriteMaterial.vert
#        ../graphics/shader/SpriteMaterial.frag
#        ../graphics/shader/Effect.vert
#        ../graphics/shader/Effect.frag
#        ../graphics/shader/ColorReduceEffect.frag
#        ../graphics/shader/InvertEffect.frag
#        ../graphics/shader/PixelateEffect.frag
#        ../graphics/shader/TintEffect.frag
#        ../graphics/shader/VignetteEffect.frag
#        shader/Test_5_03.vert
#        shader/Test_5_03.frag
#        shader/Test_5_04.frag
#        shader/Test_5_05.frag
#        shader/Test_5_06.vert
#        shader/Test_5_06.frag
#        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)
#
#file(COPY
#        images/crate.png
#        images/crate-label.png
#        images/crate-sim.png
#        images/grass.jpg
#        images/grid.png
#        images/noise.png
#        images/rolling-ball.png
#        images/sky-earth.jpg
#        images/version-1.png
#        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

# Example 01
add_executable(dgf_test_6_01 test_6_01.cpp)
target_link_libraries(dgf_test_6_01 PRIVATE Mn::DGF)
