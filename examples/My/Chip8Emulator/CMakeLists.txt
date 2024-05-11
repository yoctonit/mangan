add_executable(chip8 main.cpp src/Chip8Emulator.cpp src/Camera.cpp
        src/Chip8Memory.cpp src/Chip8Registers.cpp
        src/Chip8Stack.cpp src/Chip8Keyboard.cpp
        src/Chip8Screen.cpp src/Chip8.cpp)
target_link_libraries(chip8 PRIVATE wnd core)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.vs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.vs
        COPYONLY
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shader/basic.fs
        ${CMAKE_CURRENT_BINARY_DIR}/shader/basic.fs
        COPYONLY
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/rom/INVADERS
        ${CMAKE_CURRENT_BINARY_DIR}/INVADERS
        COPYONLY
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/rom/PONG
        ${CMAKE_CURRENT_BINARY_DIR}/PONG
        COPYONLY
)
