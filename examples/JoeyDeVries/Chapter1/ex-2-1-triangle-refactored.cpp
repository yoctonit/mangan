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

        std::vector<float> vertices{
                -0.5f, -0.5f, 0.0f, // left
                0.5f, -0.5f, 0.0f,  // right
                0.0f, 0.5f, 0.0f    // top
        };
        vbo = Mn::Vbo::FromData(vertices);

        vao.Create();
        vao.Connect(0, 3, 3, nullptr);

        // uncomment this call to draw in wireframe polygons.
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    ~HelloTriangleRefactored() {
        shader.Release();
        vbo.Release();
        vao.Release();
    }

    void Render() {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Use();
        vao.Draw(GL_TRIANGLES, 0, 3);
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Vao vao{};
};

int main() {
    Mn::Window wnd(800, 600, "Hello Triangle");
    Mn::ShowStaticScene<HelloTriangleRefactored>(wnd);
    return 0;
}
