#include "Chip8Stack.h"
#include <cassert>

void Chip8Stack::StackInBounds() const {
    assert(SP < CHIP8_TOTAL_STACK_DEPTH);
}

void Chip8Stack::Push(unsigned short val) {
    SP += 1;
    StackInBounds();
    stack_[SP] = val;
}

unsigned short Chip8Stack::Pop() {
    StackInBounds();
    unsigned short result = stack_[SP];
    SP -= 1;
    return result;
}

void Chip8Stack::Init() {
    for (int i = 0; i < CHIP8_TOTAL_STACK_DEPTH; i += 1) {
        stack_[i] = 0;
    }
    SP = 0;
}
