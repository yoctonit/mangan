#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Ebo.h"
#include "graphics/Vao.h"


class HelloTriangleIndexedRefactored {
public:
    HelloTriangleIndexedRefactored() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader = Mn::Shader::FromFiles("shader/basic.vs", "shader/basic.fs");

        std::vector<float> vertices{
                0.5f, 0.5f, 0.0f,   // top right
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.0f   // top left
        };
        std::vector<unsigned int> indices{ // note that we start from 0!
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
        };

        vao.Create();
        vbo = Mn::Vbo::FromData(vertices);
        ebo = Mn::Ebo::FromData(indices);
        vao.Connect(0, 3, 3, 0);

        // uncomment this call to draw in wireframe polygons.
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void Render() {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Use();
        vao.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    ~HelloTriangleIndexedRefactored() {
        shader.Release();
        vbo.Release();
        ebo.Release();
        vao.Release();
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Ebo ebo{};
    Mn::Vao vao{};
};

int main() {
    Mn::Window wnd(800, 600, "Hello Triangle Indexed");
    Mn::ShowStaticScene<HelloTriangleIndexedRefactored>(wnd);
    return 0;
}
