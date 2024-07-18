# prepare shader files for chapter examples
file(COPY
        ../graphics/shader/TextureMaterial.vert
        ../graphics/shader/TextureMaterial.frag
        shader/Test_5_03.vert
        shader/Test_5_03.frag
        shader/Test_5_04.frag
        shader/Test_5_05.frag
        shader/Test_5_06.vert
        shader/Test_5_06.frag
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        images/crate.png
        images/grass.jpg
        images/grid.png
        images/noise.png
        images/sky-earth.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

# Example 01
add_executable(dgf_test_5_01 test_5_01.cpp)
target_link_libraries(dgf_test_5_01 PRIVATE Mn::DGF)

# Example 02
add_executable(dgf_test_5_02 test_5_02.cpp)
target_link_libraries(dgf_test_5_02 PRIVATE Mn::DGF)

# Example 03
add_executable(dgf_test_5_03 test_5_03.cpp)
target_link_libraries(dgf_test_5_03 PRIVATE Mn::DGF)

# Example 04
add_executable(dgf_test_5_04 test_5_04.cpp)
target_link_libraries(dgf_test_5_04 PRIVATE Mn::DGF)

# Example 05
add_executable(dgf_test_5_05 test_5_05.cpp)
target_link_libraries(dgf_test_5_05 PRIVATE Mn::DGF)

# Example 06
add_executable(dgf_test_5_06 test_5_06.cpp)
target_link_libraries(dgf_test_5_06 PRIVATE Mn::DGF)
