#include "window/Window.h"
#include "src/Chip8Emulator.h"

// Chip8 Reference:
// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

int main() {
    Mn::Window wnd(
            "Chip8 Emulator",
            CHIP8_SCREEN_WIDTH * CHIP8_WINDOW_MULTIPLIER,
            CHIP8_SCREEN_HEIGHT * CHIP8_WINDOW_MULTIPLIER
    );
    return wnd.ShowScene<Chip8Emulator>();
}
