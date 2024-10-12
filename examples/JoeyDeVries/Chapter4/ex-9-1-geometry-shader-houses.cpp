#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vao.h"
#include "graphics/Vbo.h"

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Geometry Shader Example");

    bool runScene = true;
    Mn::Shader shader(
            "shader/geometry_shader.vs",
            "shader/geometry_shader.fs",
            "shader/geometry_shader.gs"
    );
    std::vector<float> points{
            -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // top-left
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // top-right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
    };
    Mn::Vbo buffer{points};
    Mn::Vao vao{true};
    vao.Connect(buffer, 0, 2, 5, 0);
    vao.Connect(buffer, 1, 3, 5, 2);

    auto &input = Mn::Window::GetInput();

    while (wnd.IsOpen() && runScene) {
        Mn::Window::PollEvents();

        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        vao.Draw(GL_POINTS, 0, 4);

        wnd.Display();
    }

    return 0;
}
