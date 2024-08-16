#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Vao.h"


class TrianglePositionColor {
public:
    TrianglePositionColor() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader = Mn::Shader::FromFiles(
                "shader/exercise-3-6.vs",
                "shader/exercise-3-6.fs"
        );
        shader.Use();

        std::vector<float> vertices{
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f, // bottom left
                0.0f, 0.5f, 0.0f,   // top
        };
        vbo = Mn::Vbo::FromData(vertices);

        vao.Create();
        vao.Connect(0, 3, 3, 0);
    }

    ~TrianglePositionColor() {
        shader.Release();
        vbo.Release();
        vao.Release();
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT);
        vao.Draw(GL_TRIANGLES, 0, 3);
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Vao vao{};
};

int main() {
    Mn::Window wnd(800, 600, "Hello Triangle");
    Mn::ShowStaticScene<TrianglePositionColor>(wnd);
    return 0;
}
