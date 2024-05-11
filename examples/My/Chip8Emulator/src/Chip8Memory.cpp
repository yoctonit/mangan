#include "Chip8Memory.h"
#include <cassert>

void Chip8Memory::IsMemoryInBounds(int index) {
    assert(index >= 0 && index < CHIP8_MEMORY_SIZE);
}

void Chip8Memory::Set(int index, unsigned char val) {
    IsMemoryInBounds(index);
    memory_[index] = val;
}

unsigned char Chip8Memory::Get(int index) const {
    IsMemoryInBounds(index);
    return memory_[index];
}

[[nodiscard]] unsigned short Chip8Memory::GetOpcode(int index) const {
    unsigned char byte1 = Get(index);
    unsigned char byte2 = Get(index + 1);
    return byte1 << 8 | byte2;
}

[[nodiscard]] const unsigned char *Chip8Memory::At(int index) const {
    IsMemoryInBounds(index);
    return &memory_[index];
}

void Chip8Memory::Init() {
    static const unsigned char default_character_set[] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // "0" Binary Hex
            0x20, 0x60, 0x20, 0x20, 0x70, // "1" Binary Hex
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // "2" Binary Hex
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // "3" Binary Hex
            0x90, 0x90, 0xF0, 0x10, 0x10, // "4" Binary Hex
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // "5" Binary Hex
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // "6" Binary Hex
            0xF0, 0x10, 0x20, 0x40, 0x40, // "7" Binary Hex
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // "8" Binary Hex
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // "9" Binary Hex
            0xF0, 0x90, 0xF0, 0x90, 0x90, // "A" Binary Hex
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // "B" Binary Hex
            0xF0, 0x80, 0x80, 0x80, 0xF0, // "C" Binary Hex
            0xE0, 0x90, 0x90, 0x90, 0xE0, // "D" Binary Hex
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // "E" Binary Hex
            0xF0, 0x80, 0xF0, 0x80, 0x80 // "F" Binary Hex
    };
    for (int i = 0; i < CHIP8_MEMORY_SIZE; i += 1) {
        memory_[i] = 0;
    }
    // std::memcpy(memory_, default_character_set, sizeof(default_character_set));;
    for (int i = CHIP8_CHARACTER_SET_LOAD_ADDRESS;
         i < CHIP8_CHARACTER_SET_LOAD_ADDRESS + sizeof(default_character_set); i += 1) {
        memory_[i] = default_character_set[i - CHIP8_CHARACTER_SET_LOAD_ADDRESS];
    }
}
