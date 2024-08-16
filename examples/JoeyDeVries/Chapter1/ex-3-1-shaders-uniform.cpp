#include <vector>
#include <cmath>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Vao.h"


class ShaderUniform {
public:
    ShaderUniform() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader = Mn::Shader::FromFiles(
                "shader/basic.vs",
                "shader/basic-color.fs");
        vertexColorLocation = glGetUniformLocation(shader.Id(), "ourColor");

        std::vector<float> vertices{
                -0.5f, -0.5f, 0.0f, // left
                0.5f, -0.5f, 0.0f,  // right
                0.0f, 0.5f, 0.0f    // top
        };
        vbo = Mn::Vbo::FromData(vertices);

        vao.Create();
        vao.Connect(0, 3, 3, 0);
    }

    ~ShaderUniform() {
        shader.Release();
        vbo.Release();
        vao.Release();
    }

    void Update(const Mn::Input &input) {
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        time += 0.01f;
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Use();

        auto greenValue = static_cast<float>(std::sin(time) / 2.0 + 0.5);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        vao.Draw(GL_TRIANGLES, 0, 3);
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Vao vao{};
    int vertexColorLocation;
    float time{};
    bool runScene{true};
};

int main() {
    Mn::Window wnd(800, 600, "Hello Triangle");
    Mn::ShowScene<ShaderUniform>(wnd);
    return 0;
}
