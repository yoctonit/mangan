#ifndef EXAMPLES_CHIP8_REGISTERS_H
#define EXAMPLES_CHIP8_REGISTERS_H

#include "Config.h"

class Chip8Registers {
public:
    unsigned char V[CHIP8_TOTAL_DATA_REGISTERS];
    unsigned short I;
    unsigned char delay_timer;
    unsigned char sound_timer;

    void Init();
// private:
    // "pseudo registers" - not accessible from Chip-8 programs
    unsigned short PC;
    // unsigned char SP;
};

#endif //EXAMPLES_CHIP8_REGISTERS_H
