add_executable(example_02_06 main.cpp src/SimpleShader.cpp src/Square.cpp src/Core.cpp)
target_link_libraries(example_02_06 PRIVATE wnd core)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/shader/simple.vs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/simple.vs
        COPYONLY
)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/shader/simple.fs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/simple.fs
        COPYONLY
)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/shader/white.fs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/white.fs
        COPYONLY
)
