#include "window/Window.h"
#include "core/Buffer.h"
#include "core/ElementBuffer.h"
#include "core/Shader.h"
#include "core/Vao.h"

#include <vector>

class Example01 {
public:
    void Initialize() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        std::vector<float> vertices{
                0.5f, 0.5f, 0.0f,   // top right
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.0f   // top left
        };
        buffer_.Create(vertices);

        std::vector<unsigned int> indices{ // note that we start from 0!
                0, 1, 3, // first triangle
                1, 2, 3 // second triangle
        };
        element_buffer_.Create(indices);

        shader_ = Mn::ShaderProgram::CreateFromFiles("basic.vs", "basic.fs");

        vao_.Create();
        vao_.Connect(buffer_, shader_, "aPos", 3, 3, nullptr);

        // Maybe new Vao method ConnectElementBuffer?
        vao_.Activate();
        element_buffer_.Activate();
        Mn::Vao::Deactivate();
    }

    void Draw() {
        glClear(GL_COLOR_BUFFER_BIT);
        shader_.Use();
//        vao_.Activate();
//        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_.Id());
//        glDrawElements();
//        vao_.Draw(GL_TRIANGLES, 0, 3);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        vao_.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Release() {
        shader_.Release();
        buffer_.Release();
        element_buffer_.Release();
        vao_.Release();
    }

private:
    Mn::Vao vao_{};
    Mn::ShaderProgram shader_{};
    Mn::Buffer buffer_{};
    Mn::ElementBuffer element_buffer_{};
};

int main() {
    Mn::Window wnd("Example01", 800, 600);
    return wnd.ShowStaticScene<Example01>();
}
