#ifndef EXAMPLES_CHIP8_CONFIG_H
#define EXAMPLES_CHIP8_CONFIG_H

inline const int CHIP8_SCREEN_WIDTH = 64;
inline const int CHIP8_SCREEN_HEIGHT = 32;
inline const int CHIP8_WINDOW_MULTIPLIER = 10;

inline const int CHIP8_MEMORY_SIZE = 4096;
inline const int CHIP8_TOTAL_DATA_REGISTERS = 16;
inline const int CHIP8_TOTAL_STACK_DEPTH = 16;
inline const int CHIP8_TOTAL_KEYS = 16;

inline const int CHIP8_CHARACTER_SET_LOAD_ADDRESS = 0x00;
inline const int CHIP8_PROGRAM_LOAD_ADDRESS = 0x200;
inline const int CHIP8_DEFAULT_SPRITE_HEIGHT = 5;

#endif //EXAMPLES_CHIP8_CONFIG_H
