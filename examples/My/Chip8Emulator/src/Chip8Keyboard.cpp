#include "window/Input.h"
#include "Chip8Keyboard.h"
#include <cassert>

void Chip8Keyboard::EnsureInBounds(int key) {
    assert(key >= 0 && key < CHIP8_TOTAL_KEYS);
}

int Chip8Keyboard::Map(int key) {
    for (int i = 0; i < CHIP8_TOTAL_KEYS; i += 1) {
        if (keyboard_map_[i] == key) {
            return i;
        }
    }
    return -1; // key not found
}

int Chip8Keyboard::Key(int key) {
    return keyboard_map_[key];
}

void Chip8Keyboard::Down(int key) {
    EnsureInBounds(key);
    keyboard[key] = true;
}

void Chip8Keyboard::Up(int key) {
    EnsureInBounds(key);
    keyboard[key] = false;
}

bool Chip8Keyboard::IsDown(int key) {
    EnsureInBounds(key);
    return keyboard[key];
}

void Chip8Keyboard::Init() {
    for (int i = 0; i < CHIP8_TOTAL_KEYS; i += 1) {
        keyboard[i] = false;
    }
    keyboard_map_[0] = Mn::Input::Key::zero;
    keyboard_map_[1] = Mn::Input::Key::one;
    keyboard_map_[2] = Mn::Input::Key::two;
    keyboard_map_[3] = Mn::Input::Key::three;
    keyboard_map_[4] = Mn::Input::Key::four;
    keyboard_map_[5] = Mn::Input::Key::five;
    keyboard_map_[6] = Mn::Input::Key::six;
    keyboard_map_[7] = Mn::Input::Key::seven;
    keyboard_map_[8] = Mn::Input::Key::eight;
    keyboard_map_[9] = Mn::Input::Key::nine;
    keyboard_map_[10] = Mn::Input::Key::a;
    keyboard_map_[11] = Mn::Input::Key::b;
    keyboard_map_[12] = Mn::Input::Key::c;
    keyboard_map_[13] = Mn::Input::Key::d;
    keyboard_map_[14] = Mn::Input::Key::e;
    keyboard_map_[15] = Mn::Input::Key::f;
}

void Chip8Keyboard::Update(const Mn::Input &input) {
    for (int i = 0; i < CHIP8_TOTAL_KEYS; i += 1) {
        if (input.IsPressedKey(Key(i))) {
            Down(i);
        } else {
            Up(i);
        }
    }
}