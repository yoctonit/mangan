# prepare shader files for chapter examples
file(COPY
        ../graphics/shader/BasicMaterial.vert
        ../graphics/shader/BasicMaterial.frag
        shader/Test_4_04.vert
        shader/Test_4_04.frag
        shader/Test_4_05.vert
        shader/Test_4_05.frag
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

# Example 01
add_executable(dgf_test_4_01 test_4_01.cpp)
target_link_libraries(dgf_test_4_01 PRIVATE Mn::DGF)

# Example 02
add_executable(dgf_test_4_02 test_4_02.cpp)
target_link_libraries(dgf_test_4_02 PRIVATE Mn::DGF)

# Example 03
add_executable(dgf_test_4_03 test_4_03.cpp)
target_link_libraries(dgf_test_4_03 PRIVATE Mn::DGF)

# Example 04
add_executable(dgf_test_4_04 test_4_04.cpp)
target_link_libraries(dgf_test_4_04 PRIVATE Mn::DGF)

# Example 05
add_executable(dgf_test_4_05 test_4_05.cpp)
target_link_libraries(dgf_test_4_05 PRIVATE Mn::DGF)

# Example 06
add_executable(dgf_test_4_06 test_4_06.cpp)
target_link_libraries(dgf_test_4_06 PRIVATE Mn::DGF)
