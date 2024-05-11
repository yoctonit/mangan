#ifndef EXAMPLES_CHIP8_STACK_H
#define EXAMPLES_CHIP8_STACK_H

#include "Config.h"

class Chip8Stack {
public:
    void Push(unsigned short val);

    [[nodiscard]] unsigned short Pop();

    void Init();

private:
    unsigned short stack_[CHIP8_TOTAL_STACK_DEPTH];
    unsigned char SP; // "pseudo register" - not accessible from Chip-8 programs

    void StackInBounds() const;
};

#endif //EXAMPLES_CHIP8_STACK_H
