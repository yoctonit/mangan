#ifndef EXAMPLES_CHIP8_CHIP8_H
#define EXAMPLES_CHIP8_CHIP8_H


#include "Config.h"
#include "Chip8Memory.h"
#include "Chip8Registers.h"
#include "Chip8Stack.h"
#include "Chip8Keyboard.h"
#include "Chip8Screen.h"
#include <random>

struct Chip8 {
    Chip8Memory memory;
    Chip8Stack stack;
    Chip8Registers registers;
    Chip8Keyboard keyboard;
    Chip8Screen screen;

    Chip8();

    void Init();

    void Load(const char *buf, size_t size);

    void Exec(unsigned short opcode);

    void Test();

private:
    void ExecExtended(unsigned short opcode);

    void ExecExtended8(unsigned short opcode, unsigned char x, unsigned char y);

    void ExecExtendedE(unsigned short opcode, unsigned char x);

    void ExecExtendedF(unsigned short opcode, unsigned char x);

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> distr;
};

#endif //EXAMPLES_CHIP8_CHIP8_H
