#include "Chip8.h"
#include <cassert>
//#include <iostream>


Chip8::Chip8() : gen(rd()), distr(std::uniform_int_distribution<>(0, 255)) {}

void Chip8::Init() {
    memory.Init();
    stack.Init();
    registers.Init();
    keyboard.Init();
    screen.Init();
}

void Chip8::Load(const char *buf, size_t size) {
    assert(size + CHIP8_PROGRAM_LOAD_ADDRESS < CHIP8_MEMORY_SIZE);
    for (int i = 0; i < size; i += 1) {
        memory.Set(CHIP8_PROGRAM_LOAD_ADDRESS + i, buf[i]);
    }
    registers.PC = CHIP8_PROGRAM_LOAD_ADDRESS;
}

void Chip8::Exec(unsigned short opcode) {
    switch (opcode) {
        case 0x00E0: // CLS: Clear the display
            screen.Clear();
            break;

        case 0x00EE: // RET: Return from subroutine
            registers.PC = stack.Pop();
            break;

        default:
            ExecExtended(opcode);
    }
}

void Chip8::ExecExtended(unsigned short opcode) {
    unsigned short nnn = opcode & 0x0fff;
    unsigned char x = (opcode >> 8) & 0x000f;
    unsigned char y = (opcode >> 4) & 0x000f;
    unsigned char kk = opcode & 0x00ff;
    unsigned char n = opcode & 0x00f;

    switch (opcode & 0xf000) {
        case 0x1000: // 1nnn - JP addr: Jump to location nnn
            registers.PC = nnn;
            break;

        case 0x2000: // 2nnn- CALL addr: Call subroutine at nnn
            stack.Push(registers.PC);
            registers.PC = nnn;
            break;

        case 0x3000: // 3xkk - SE Vx, byte: Skip next instruction if Vx = kk
            if (registers.V[x] == kk) {
                registers.PC += 2;
            }
            break;

        case 0x4000: // 4xkk - SNE Vx, byte: Skip next instruction if Vx != kk
            if (registers.V[x] != kk) {
                registers.PC += 2;
            }
            break;

        case 0x5000: // 5xy0 - SE Vx, Vy: Skip next instruction if Vx = Vy
            if (registers.V[x] == registers.V[y]) {
                registers.PC += 2;
            }
            break;

        case 0x6000: // 6xkk - LD Vx, byte: Set Vx = kk
            registers.V[x] = kk;
            break;

        case 0x7000: // 7xkk - ADD Vx, byte: Set Vx = Vx + kk
            registers.V[x] += kk;
            break;

        case 0x8000: // 8xy. opcodes
            ExecExtended8(opcode, x, y);
            break;

        case 0x9000: // 9xy0 - SNE Vx, Vy: Skip next instruction if Vx != Vy
            if (registers.V[x] != registers.V[y]) {
                registers.PC += 2;
            }
            break;

        case 0xA000: // Annn - LD I, addr: Set I = nnn
            registers.I = nnn;
            break;

        case 0xB000: // Bnnn - JP V0, addr: Jump to location nnn + V0
            registers.PC = nnn + registers.V[0x00];
            break;

        case 0xC000: // Cxkk - RND Vx, byte: Set Vx = random byte and kk
            registers.V[x] = distr(gen) & kk;
            break;

        case 0xD000: // Dxyn - DRW Vx, Vy, nibble: Display n byte sprite starting and memory location I at (Vx, Vy), set VF = collision
            registers.V[0x0f] = screen.DrawSprite(registers.V[x], registers.V[y], memory.At(registers.I), n);
            break;

        case 0xE000: // Ex.. opcodes
            ExecExtendedE(opcode, x);
            break;

        case 0xF000: // Fx.. opcodes
            ExecExtendedF(opcode, x);
            break;
    }
}

void Chip8::ExecExtended8(unsigned short opcode, unsigned char x, unsigned char y) {
    unsigned char sub_opcode = opcode & 0x000f;
    unsigned short tmp = 0;

    switch (sub_opcode) {
        case 0x00: // 8xy0 - LD Vx, Vy: Set Vx = Vy
            registers.V[x] = registers.V[y];
            break;

        case 0x0001: // 8xy1 - OR Vx, Vy: Set Vx = Vx OR Vy
            registers.V[x] |= registers.V[y];
            break;

        case 0x0002: // 8xy2 - AND Vx, Vy: Set Vx = Vx AND Vy
            registers.V[x] &= registers.V[y];
            break;

        case 0x0003: // 8xy3 - XOR Vx, Vy: Set Vx = Vx XOR Vy
            registers.V[x] ^= registers.V[y];
            break;

        case 0x0004: // 8xy4 - ADD Vx, Vy: Set Vx = Vx + Vy, Vf = carry
            tmp = registers.V[x] + registers.V[y];
            registers.V[x] += registers.V[y];

            registers.V[0x0f] = 0;
            if (tmp > 0xff) {
                registers.V[0x0f] = 1;
            }
            break;

        case 0x0005: // 8xy5 - SUB Vx, Vy: Set Vx = Vx - Vy, Vf = NOT borrow
            registers.V[0x0f] = 0;
            if (registers.V[x] > registers.V[y]) {
                registers.V[0x0f] = 1;
            }
            registers.V[x] -= registers.V[y];
            break;

        case 0x0006: // 8xy6 - SHR Vx {, Vy}: Set Vx = Vx SHR 1
            registers.V[0x0f] = registers.V[x] & 0x01;
            registers.V[x] /= 2;
            break;

        case 0x0007: // 8xy7 - SUBN Vx, Vy: Set Vx = Vy - Vx, Vf = NOT borrow
            registers.V[0x0f] = 0;
            if (registers.V[y] > registers.V[x]) {
                registers.V[0x0f] = 1;
            }
            registers.V[x] = registers.V[y] - registers.V[x];
            break;

        case 0x000E: // 8xyE - SHL Vx {, Vy}: Set Vx = Vx SHL 1
            registers.V[0x0f] = registers.V[x] & 0x80;
            registers.V[x] *= 2;
            break;

        default:
            screen.Clear(); // maybe throw instead
    }
}

void Chip8::ExecExtendedE(unsigned short opcode, unsigned char x) {
    unsigned char sub_opcode = opcode & 0x00ff;

    switch (sub_opcode) {
        case 0x9E: // Ex9E - SKP Vx: Skip next instruction if key with the value of Vx is pressed
            if (keyboard.IsDown(registers.V[x])) {
                registers.PC += 2;
            }
            break;

        case 0xA1: // Ex9E - SKNP Vx: Skip next instruction if key with the value of Vx is not pressed
            if (!keyboard.IsDown(registers.V[x])) {
                registers.PC += 2;
            }
            break;

        default:
            screen.Clear(); // maybe throw instead
    }
}

void Chip8::ExecExtendedF(unsigned short opcode, unsigned char x) {
    unsigned char sub_opcode = opcode & 0x00ff;
    bool exit_loop = false;
    unsigned char tmp = 0;

    switch (sub_opcode) {
        case 0x07: // Fx07 - LD Vx, DT: Vx = delay timer value
            registers.V[x] = registers.delay_timer;
            break;

        case 0x0A: // Fx0A - LD Vx, K: Wait for a key press, store the value of the key in Vx
//            while (!exit_loop) {
//                for (int i = 0; i < CHIP8_TOTAL_KEYS; i += 1) {
//                    if (keyboard.IsDown(i)) {
//                        registers.V[x] = i;
//                        exit_loop = true;
//                        break;
//                    }
//                }
//            }
            for (int i = 0; i < CHIP8_TOTAL_KEYS; i += 1) {
                if (keyboard.IsDown(i)) {
                    registers.V[x] = i;
                    exit_loop = true;
                    break;
                }
            }
            if (!exit_loop) {
                registers.PC -= 2;
            }
            break;

        case 0x15: // Fx15 - LD DT, Vx: Set delay timer = Vx
            registers.delay_timer = registers.V[x];
            break;

        case 0x18: // Fx18 - LD ST, Vx: Set sound timer = Vx
            registers.sound_timer = registers.V[x];
            break;

        case 0x1E: // Fx1E - ADD I, Vx: Set I = I + Vx
            registers.I += registers.V[x];
            break;

        case 0x29: // Fx29 - LD F, Vx: Set I = location of sprite for digit Vx
            registers.I = CHIP8_CHARACTER_SET_LOAD_ADDRESS + CHIP8_DEFAULT_SPRITE_HEIGHT * registers.V[x];
            break;

        case 0x33: // Fx33 - LD B, Vx: Store BCD representation of Vx in memory locations I, I + 1, I +2
            tmp = registers.V[x] / 100;
            memory.Set(registers.I, CHIP8_CHARACTER_SET_LOAD_ADDRESS + CHIP8_DEFAULT_SPRITE_HEIGHT * tmp);
            tmp = (registers.V[x] - tmp * 100) / 10;
            memory.Set(registers.I + 1, CHIP8_CHARACTER_SET_LOAD_ADDRESS + CHIP8_DEFAULT_SPRITE_HEIGHT * tmp);
            tmp = registers.V[x] % 10;
            memory.Set(registers.I + 2,
                       CHIP8_CHARACTER_SET_LOAD_ADDRESS + CHIP8_DEFAULT_SPRITE_HEIGHT * tmp);
            break;

        case 0x55: // Fx55 - LD [I], Vx: Store registers V0 through Vx from memory starting at location I
            for (int i = 0; i <= x; i += 1) {
                memory.Set(registers.I + i, registers.V[i]);
            }
            break;

        case 0x65: // Fx65 - Vx, LD [I]: Read registers V0 through Vx from memory starting at location I
            for (int i = 0; i <= x; i += 1) {
                registers.V[i] = memory.Get(registers.I + i);
            }
            break;

        default:
            screen.Clear(); // maybe throw instead
    }
}

void Chip8::Test() {
    // 8xy4 - ADD Vx, Vy: Set Vx = Vx + Vy, Vf = carry
    registers.V[0] = 200;
    registers.V[1] = 50;
    Exec(0x8014);
    assert(registers.V[0x00] == 250);
    assert(registers.V[0x0f] == 0);

    registers.V[0] = 200;
    registers.V[1] = 60;
    Exec(0x8014);
    assert(registers.V[0x00] == 4);
    assert(registers.V[0x0f] == 1);

    // 8xy5 - SUB Vx, Vy: Set Vx = Vx - Vy, Vf = NOT borrow
    registers.V[0] = 200;
    registers.V[1] = 50;
    Exec(0x8015);
    assert(registers.V[0x00] == 150);
    assert(registers.V[0x0f] == 1);

    registers.V[0] = 50;
    registers.V[1] = 60;
    Exec(0x8015);
    // assert(registers.V[0x00] == -10);
    assert(registers.V[0x0f] == 0);

    // 8xy6 - SHR Vx {, Vy}: Set Vx = Vx SHR 1
    registers.V[0] = 50;
    Exec(0x8016);
    assert(registers.V[0x00] == 25);
    assert(registers.V[0x0f] == 0);

    registers.V[0] = 51;
    Exec(0x8016);
    assert(registers.V[0x00] == 25);
    assert(registers.V[0x0f] == 1);

}