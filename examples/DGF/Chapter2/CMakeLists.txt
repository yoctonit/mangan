# Example 01
add_executable(dgf_02_01_empty e01_empty.cpp)
target_link_libraries(dgf_02_01_empty PRIVATE Mn::Engine)

add_executable(dgf_test_2_01 test_2_01.cpp)
target_link_libraries(dgf_test_2_01 PRIVATE Mn::DGF)

# prepare shader files for chapter examples
file(COPY shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Example 02
add_executable(dgf_02_02_point e02_point.cpp)
target_link_libraries(dgf_02_02_point PRIVATE Mn::Engine)

add_executable(dgf_test_2_02 test_2_02.cpp)
target_link_libraries(dgf_test_2_02 PRIVATE Mn::DGF)


#add_executable(shape e03_shape.cpp)
#target_link_libraries(shape mangan1)
#
#add_executable(shape2 e04_shape.cpp)
#target_link_libraries(shape2 mangan1)
#
#add_executable(shape3 e05_shape.cpp)
#target_link_libraries(shape3 mangan1)
#
#add_executable(shape4 e06_shape.cpp)
#target_link_libraries(shape4 mangan1)
#
#add_executable(shape5 e07_shape.cpp)
#target_link_libraries(shape5 mangan1)
#
#add_executable(shape6 e08_shape.cpp)
#target_link_libraries(shape6 mangan1)
#
#add_executable(shape7 e09_shape.cpp)
#target_link_libraries(shape7 mangan1)
#
#add_custom_command(
#    TARGET point POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    ${CMAKE_CURRENT_SOURCE_DIR}/shader/point.vert
#    ${CMAKE_CURRENT_BINARY_DIR}/shader/point.vert)
