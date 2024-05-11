#ifndef EXAMPLES_CHIP8_CHIP8_EMULATOR_H
#define EXAMPLES_CHIP8_CHIP8_EMULATOR_H

#include "window/Input.h"
#include "core/Shader.h"
#include "core/Buffer.h"
#include "core/Vao.h"
#include "Camera.h"

#include "Chip8.h"

#include <vector>

class Chip8Emulator {
public:
    void Initialize(int window_width, int window_height, const std::string& file_name = "PONG");

    void Release();

    void Draw() const;

    void Update(const Mn::Input &input);

    [[nodiscard]] bool ShouldClose() const;

private:
    float window_width_;
    float window_height_;
    bool should_close_{};

    Mn::ShaderProgram shader_{};
    Mn::Buffer buffer_{};
    Mn::Vao vao_{};
    Camera camera_{};
    std::vector<float> pixels_;

    Chip8 chip8;
};

#endif //EXAMPLES_CHIP8_CHIP8_EMULATOR_H
