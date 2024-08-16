#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Vao.h"


class HelloTriangleRefactored {
public:
    HelloTriangleRefactored() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader = Mn::Shader::FromFiles("shader/basic.vs", "shader/basic.fs");

        std::vector<float> vertices1{
                // first triangle
                -0.9f, -0.5f, 0.0f,  // left
                -0.0f, -0.5f, 0.0f,  // right
                -0.45f, 0.5f, 0.0f,  // top
        };
        std::vector<float> vertices2{
                // second triangle
                0.0f, -0.5f, 0.0f,  // left
                0.9f, -0.5f, 0.0f,  // right
                0.45f, 0.5f, 0.0f   // top
        };
        vbo1 = Mn::Vbo::FromData(vertices1);
        vbo2 = Mn::Vbo::FromData(vertices2);

        vao1.Create();
        vbo1.Activate();
        vao1.Connect(0, 3, 3, 0);

        vao2.Create();
        vbo2.Activate();
        vao2.Connect(0, 3, 3, 0);

        // uncomment this call to draw in wireframe polygons.
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    ~HelloTriangleRefactored() {
        shader.Release();
        vbo1.Release();
        vbo2.Release();
        vao1.Release();
        vao2.Release();
    }

    void Render() {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Use();
        vao1.Draw(GL_TRIANGLES, 0, 3);
        vao2.Draw(GL_TRIANGLES, 0, 3);
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo1{};
    Mn::Vbo vbo2{};
    Mn::Vao vao1{};
    Mn::Vao vao2{};
};

int main() {
    Mn::Window wnd(800, 600, "Hello Triangle");
    Mn::ShowStaticScene<HelloTriangleRefactored>(wnd);
    return 0;
}
