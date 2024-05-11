add_library(wnd src/Window.cpp src/Input.cpp)

target_link_libraries(wnd PRIVATE glfw)
target_link_libraries(wnd PUBLIC glad_4_3)

target_include_directories(wnd PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(Mn::Window ALIAS wnd)
