file(COPY
        assets/bg_clip.mp3
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/sounds)

add_executable(byo2dge_ex_04_06 main.cpp)
# target_link_libraries(byo2dge_ex_04_05 PRIVATE Mn::Engine)
