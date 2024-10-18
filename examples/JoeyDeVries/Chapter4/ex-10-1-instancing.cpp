#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vao.h"
#include "graphics/Vbo.h"
#include "Camera.h"

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Instancing Example");

    bool runScene = true;

    Mn::Shader shader(
            "shader/instancing.vs",
            "shader/instancing.fs"
    );

    // generate a list of 100 quad locations/translation-vectors
    // ---------------------------------------------------------
    std::vector<float> translations;
    float offset = 0.1f;
    for (int y = -10; y < 10; y += 2) {
        for (int x = -10; x < 10; x += 2) {
            glm::vec2 translation;
            translation.x = (float) x / 10.0f + offset;
            translation.y = (float) y / 10.0f + offset;

            translations.push_back(translation.x);
            translations.push_back(translation.y);
        }
    }
    Mn::Vbo instanceVBO{translations};

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> quadVertices{
            // positions     // colors
            -0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
            0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
            -0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

            -0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
            0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
            0.05f, 0.05f, 0.0f, 1.0f, 1.0f
    };
    Mn::Vbo quadVBO{quadVertices};

    Mn::Vao quadVao{true};
    quadVao.Connect(quadVBO, 0, 2, 5, 0);
    quadVao.Connect(quadVBO, 1, 3, 5, 2);
    quadVao.Connect(instanceVBO, 2, 2, 2, 0);
    glVertexAttribDivisor(2, 1);

    auto &input = Mn::Window::GetInput();

    while (wnd.IsOpen() && runScene) {
        Mn::Window::PollEvents();

        input.Update();

        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw 100 instanced quads
        shader.Use();
        quadVao.Activate();
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each

        wnd.Display();
    }

    return 0;
}
