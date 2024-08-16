#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Vao.h"


class TriangleOffset {
public:
    TriangleOffset() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader = Mn::Shader::FromFiles(
                "shader/basic-pos-color-attr-offset.vs",
                "shader/basic-pos-color-attr.fs"
        );
        shader.Use();
        xOffsetLocation = glGetUniformLocation(shader.Id(), "xOffset");
        yOffsetLocation = glGetUniformLocation(shader.Id(), "yOffset");

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

    ~TriangleOffset() {
        shader.Release();
        vbo.Release();
        vao.Release();
    }

    void Update(const Mn::Input &input) {
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }
        if (input.IsPressedKey(MN_KEY_RIGHT)) {
            xOffset += 0.01f;
            if (xOffset > 1.0f) xOffset = 1.0f;
        } else if (input.IsPressedKey(MN_KEY_LEFT)) {
            xOffset -= 0.01f;
            if (xOffset < -1.0f) xOffset = -1.0f;
        }
        if (input.IsPressedKey(MN_KEY_UP)) {
            yOffset += 0.01f;
            if (yOffset > 1.0f) yOffset = 1.0f;
        } else if (input.IsPressedKey(MN_KEY_DOWN)) {
            yOffset -= 0.01f;
            if (yOffset < -1.0f) yOffset = -1.0f;
        }
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT);
        glUniform1f(xOffsetLocation, xOffset);
        glUniform1f(yOffsetLocation, yOffset);
        vao.Draw(GL_TRIANGLES, 0, 3);
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Vao vao{};
    int xOffsetLocation{};
    int yOffsetLocation{};
    float xOffset{};
    float yOffset{};
    bool runScene{true};
};

int main() {
    Mn::Window wnd(800, 600, "Hello Triangle");
    Mn::ShowScene<TriangleOffset>(wnd);
    return 0;
}
