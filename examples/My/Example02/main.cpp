#include "window/Window.h"
#include "core/Shader.h"
#include "core/Buffer.h"
#include <iostream>

class Example02 {
public:
    Example02() = default;

    ~Example02() {
        shader1_.Release();
        shader2_.Release();
        buffer_.Release();
    }

    void Initialize() {
        std::cout << "shader1.Id() before creation: " << shader1_.Id() << '\n';
        shader1_ = Mn::ShaderProgram::CreateFromFiles("basic.vs", "basic.fs");
        std::cout << "shader1.Id(): " << shader1_.Id() << '\n';
        shader2_ = Mn::ShaderProgram::CreateFromFiles("basic.vs", "basic.fs");
        std::cout << "shader2.Id(): " << shader2_.Id() << '\n';

        const std::vector<float> vertices{
                -0.5f,-0.22867f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.22867f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.57735f,  0.0f, 0.0f, 0.0f, 1.0f
        };
        std::cout << "buffer_.Id() before initialization: " << buffer_.Id() << '\n';
        // buffer_ = Mn::Buffer(vertices);
        buffer_ = CreateBuffer();
        std::cout << "buffer_.Id(): " << buffer_.Id() << '\n';
        Mn::Buffer buffer2 = buffer_;
        std::cout << "buffer2.Id(): " << buffer2.Id() << '\n';
    }

    Mn::Buffer CreateBuffer() {
        const std::vector<float> vertices{
                -0.5f,-0.22867f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.22867f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.57735f,  0.0f, 0.0f, 0.0f, 1.0f
        };
        Mn::Buffer buffer(vertices);
        return buffer;
    }

    void Draw() const {}

    void Release() {}

private:
    Mn::ShaderProgram shader1_;
    Mn::ShaderProgram shader2_;
    Mn::Buffer buffer_;
};

int main() {
    Mn::Window wnd("Example02", 800, 600);
    return wnd.ShowStaticScene<Example02>();
}
