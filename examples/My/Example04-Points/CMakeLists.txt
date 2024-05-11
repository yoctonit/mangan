add_executable(example04-points main.cpp src/Point.cpp src/PointsScene.cpp src/Camera.cpp src/Util.cpp)
target_link_libraries(example04-points PRIVATE wnd core)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vs
        COPYONLY
)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.fs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.fs
        COPYONLY
)
