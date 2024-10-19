#include <iostream>
#include "window/Window.h"
#include "core/Shader.h"
#include "core/Vbo.h"


int main() {
    Mn::Window wnd(800, 600, "Example");

    Mn::Shader shader1;
    Mn::Shader shader2;

    std::cout << "shader1.Id() before creation: " << shader1.Id() << '\n';
    shader1 = Mn::Shader{"shader/basic.vs.glsl", "shader/basic.fs.glsl"};
    std::cout << "shader1.Id() after creation: " << shader1.Id() << '\n';

    std::cout << "shader2.Id() before creation: " << shader2.Id() << '\n';
    shader2 = Mn::Shader{"shader/basic.vs.glsl", "shader/basic.fs.glsl"};
    std::cout << "shader2.Id() after creation: " << shader2.Id() << '\n';

    const std::vector<float> vertices{
            -0.5f, -0.22867f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.22867f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.57735f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    Mn::Vbo buffer;
    std::cout << "buffer_.Id() before initialization: " << buffer.Id() << '\n';
    buffer = Mn::Vbo(vertices);
    std::cout << "buffer_.Id() after creation: " << buffer.Id() << '\n';

    Mn::Vbo buffer2 = buffer;
    std::cout << "buffer2.Id(): " << buffer2.Id() << '\n';

    auto &input = Mn::Window::GetInput();
    while (wnd.IsOpen()) {
        Mn::Window::PollEvents();
        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            wnd.Close();
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        wnd.Display();
    }

    return 0;
}
