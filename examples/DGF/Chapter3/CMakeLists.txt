# Example 01 is test for custom Vector and Matrix classes from the book,
# but here I use glm library instead, so I skip this example

# prepare shader files for chapter examples
file(COPY
        shader/Test_3_02.vert
        shader/Test_3_02.frag
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

# Example 02
add_executable(dgf_test_3_02 test_3_02.cpp)
target_link_libraries(dgf_test_3_02 PRIVATE Mn::DGF)
