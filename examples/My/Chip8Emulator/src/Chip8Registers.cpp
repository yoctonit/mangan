#include "Chip8Registers.h"

void Chip8Registers::Init() {
    for (int i = 0; i < CHIP8_TOTAL_DATA_REGISTERS; i += 1) {
        V[i] = 0;
    }
    I = 0;
    delay_timer = 0;
    sound_timer = 0;
    PC = 0;
}
