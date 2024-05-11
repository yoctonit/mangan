#ifndef EXAMPLES_CHIP8_MEMORY_H
#define EXAMPLES_CHIP8_MEMORY_H

#include "Config.h"

class Chip8Memory {
public:
    void Set(int index, unsigned char val);

    [[nodiscard]] unsigned char Get(int index) const;

    [[nodiscard]] unsigned short GetOpcode(int index) const;

    [[nodiscard]] const unsigned char *At(int index) const;

    static void IsMemoryInBounds(int index);

    void Init();

private:
    unsigned char memory_[CHIP8_MEMORY_SIZE];
};

#endif //EXAMPLES_CHIP8_MEMORY_H
