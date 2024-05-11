#include "Chip8Emulator.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
//#include <chrono>
//#include <thread>
#include <windows.h>

void Chip8Emulator::Initialize(int window_width, int window_height, const std::string &file_name) {
    window_width_ = static_cast<float>(window_width);
    window_height_ = static_cast<float>(window_height);

    shader_ = Mn::ShaderProgram::CreateFromFiles("shader/basic.vs", "shader/basic.fs");

    buffer_.Create(CHIP8_SCREEN_WIDTH * CHIP8_SCREEN_HEIGHT * 2 * sizeof(float), GL_DYNAMIC_DRAW);

    vao_.Create();
    vao_.Connect(buffer_, shader_, "a_position", 2, 0, nullptr);

    camera_.Create({32.0f, -16.0f}, 64, {0, 0, window_width_, window_height_});
    camera_.BackgroundColor({0.1f, 0.1f, 0.1f, 1.0f});
    camera_.SetViewAndCameraMatrix();

    chip8.Init();

    std::ifstream file_stream(file_name, std::ios::in | std::ios::binary);
    if (!file_stream.is_open()) {
        std::cerr << "Could not open " << file_name << "\n";
    }

    std::stringstream str;
    str << file_stream.rdbuf();
    file_stream.close();

    chip8.Load(str.str().data(), str.str().size());
}

void Chip8Emulator::Release() {
    shader_.Release();
    buffer_.Release();
    vao_.Release();
}

void Chip8Emulator::Draw() const {
    camera_.Clear();

    shader_.Use();
    Mn::ShaderProgram::Uniform(shader_.UniformLocation("u_camera_matrix"), camera_.CameraMatrix());

    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(10.0);
    int cnt = static_cast<int>(pixels_.size() / 2);
    vao_.Draw(GL_POINTS, 0, cnt);
}

void Chip8Emulator::Update(const Mn::Input &input) {
    if (input.IsClickedKey(Mn::Input::Key::esc)) {
        should_close_ = true;
    }

    for (int i = 0; i < CHIP8_TOTAL_KEYS; i += 1) {
        if (input.IsPressedKey(chip8.keyboard.Key(i))) {
            chip8.keyboard.Down(i);
        } else {
            chip8.keyboard.Up(i);
        }
    }

    pixels_.clear();
    for (int y = 0; y < CHIP8_SCREEN_HEIGHT; y += 1) {
        for (int x = 0; x < CHIP8_SCREEN_WIDTH; x += 1) {
            if (chip8.screen.IsPixelSet(x, y)) {
                pixels_.push_back(static_cast<float>(x) + 0.5f);
                pixels_.push_back(-static_cast<float>(y) - 0.5f);
            }
        }
    }
    buffer_.Load(pixels_);

    if (chip8.registers.delay_timer > 0) {
        chip8.registers.delay_timer -= 1;
        // Sleep(1);
        // std::this_thread::sleep_for(std::chrono::milliseconds(50));
        // std::cout << "Delay!\n";
    }

    if (chip8.registers.sound_timer > 0) {
        chip8.registers.sound_timer -= 1;
        // Beep(432, 1);
        // std::cout << '\a';
//        Beep(432, 100 * chip8.registers.sound_timer);
//        chip8.registers.sound_timer = 0;
    }

    unsigned short opcode = chip8.memory.GetOpcode(chip8.registers.PC);
    chip8.registers.PC += 2;
    chip8.Exec(opcode);
}

[[nodiscard]] bool Chip8Emulator::ShouldClose() const {
    return should_close_;
}
