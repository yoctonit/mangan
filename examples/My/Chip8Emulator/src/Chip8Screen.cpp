#include "Chip8Screen.h"
#include "Config.h"

#include <cassert>
#include <iostream>

void Chip8Screen::Init() {
    for (int y = 0; y < CHIP8_SCREEN_HEIGHT; y += 1) {
        for (int x = 0; x < CHIP8_SCREEN_WIDTH; x += 1) {
            pixels_.push_back(false);
        }
    }
}

void Chip8Screen::SetPixel(int x, int y) {
    CheckBounds(x, y);
    pixels_[y * CHIP8_SCREEN_WIDTH + x] = true;
}

bool Chip8Screen::IsPixelSet(int x, int y) const {
    CheckBounds(x, y);
    return pixels_[y * CHIP8_SCREEN_WIDTH + x];
}

void Chip8Screen::CheckBounds(int x, int y) {
    assert(x >= 0 && x < CHIP8_SCREEN_WIDTH);
    assert(y >= 0 && y < CHIP8_SCREEN_HEIGHT);
}

bool Chip8Screen::DrawSprite(int x, int y, const unsigned char *sprite, int num) {
    bool pixel_collision = false;

    for (int ly = 0; ly < num; ly += 1) {
        unsigned char c = sprite[ly];
        for (int lx = 0; lx < 8; lx += 1) {
            if ((c & (0b10000000 >> lx)) == 0) {
                continue;
            }
            int y_offset = (y + ly) % CHIP8_SCREEN_HEIGHT;
            int x_offset = (x + lx) % CHIP8_SCREEN_WIDTH;
            if (pixels_[y_offset * CHIP8_SCREEN_WIDTH + x_offset]) {
                pixel_collision = true;
            }
            pixels_[y_offset * CHIP8_SCREEN_WIDTH + x_offset] = !pixels_[y_offset * CHIP8_SCREEN_WIDTH + x_offset];
            //  pixels_[y_offset * CHIP8_SCREEN_WIDTH + x_offset] ^= true;
        }
    }
    return pixel_collision;
}

void Chip8Screen::Clear() {
    for (int i = 0; i < pixels_.size(); i += 1) {
        pixels_[i] = false;
    }
}