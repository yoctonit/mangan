#ifndef EXAMPLES_CHIP8_KEYBOARD_H
#define EXAMPLES_CHIP8_KEYBOARD_H

#include "Config.h"
#include "window/Input.h"

class Chip8Keyboard {
public:
    int Map(int key);

    int Key(int key);

    void Down(int key);

    void Up(int key);

    bool IsDown(int key);

    void Init();

    void Update(const Mn::Input &input);

private:
    bool keyboard[CHIP8_TOTAL_KEYS];
    int keyboard_map_[CHIP8_TOTAL_KEYS];

    static void EnsureInBounds(int key);
};

#endif //EXAMPLES_CHIP8_KEYBOARD_H
