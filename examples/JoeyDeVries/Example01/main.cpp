#include "window/Window.h"
#include "core/Buffer.h"
#include "core/Shader.h"
#include "core/Vao.h"

#include <vector>

class Example01 {
public:
    void Initialize() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        std::vector<float> vertices = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };
        buffer_ = Mn::Buffer(vertices);

        shader_ = Mn::ShaderProgram::CreateFromFiles("basic.vs", "basic.fs");

        vao_.Create();
        vao_.Connect(buffer_, shader_, "aPos", 3, 3, nullptr);
    }

    void Draw() {
        glClear(GL_COLOR_BUFFER_BIT);
        shader_.Use();
        vao_.Draw(GL_TRIANGLES, 0, 3);
    }

    void Release() {
        shader_.Release();
        buffer_.Release();
    }

private:
    Mn::Vao vao_{};
    Mn::ShaderProgram shader_{};
    Mn::Buffer buffer_{};
};

int main() {
    Mn::Window wnd("Example01", 800, 600);
    return wnd.ShowStaticScene<Example01>();
}
