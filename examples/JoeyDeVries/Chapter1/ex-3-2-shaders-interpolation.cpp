#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Vao.h"


class ShaderInterpolation {
public:
    ShaderInterpolation() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader = Mn::Shader::FromFiles(
                "shader/basic-pos-color-attr.vs",
                "shader/basic-pos-color-attr.fs"
        );
        shader.Use();

        std::vector<float> vertices{
                // positions       // colors
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
                0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
        };
        vbo = Mn::Vbo::FromData(vertices);

        vao.Create();
        vao.Connect(0, 3, 6, 0);
        vao.Connect(1, 3, 6, 3);
    }

    ~ShaderInterpolation() {
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
    Mn::ShowStaticScene<ShaderInterpolation>(wnd);
    return 0;
}
