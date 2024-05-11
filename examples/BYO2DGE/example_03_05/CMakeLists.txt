add_executable(example_03_05 main.cpp
        src/SimpleShader.cpp src/Square.cpp src/Engine.cpp
        src/Renderable.cpp src/Transform.cpp src/Camera.cpp)
target_link_libraries(example_03_05 PRIVATE wnd core)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/shader/simple.vs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/simple.vs
        COPYONLY
)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/shader/simple.fs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/simple.fs
        COPYONLY
)
