#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Ebo.h"
#include "graphics/Vao.h"
#include "graphics/Uniform.h"
#include "graphics/Texture.h"


class TexturedRectangle {
public:
    TexturedRectangle() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader = Mn::Shader::FromFiles(
                "shader/texture.vs",
                "shader/exercise-4-6.fs"
        );
        texture1Uniform.Create(shader.Locate("texture1"), Mn::Uniform::Type::Int);
        texture1Uniform = 0;
        texture2Uniform.Create(shader.Locate("texture2"), Mn::Uniform::Type::Int);
        texture2Uniform = 1;
        mixValueUniform.Create(shader.Locate("mixValue"), Mn::Uniform::Type::Float);
        mixValueUniform = mixValue;

        vao.Create();

        std::vector<float> vertices{
                // positions         // colors           // texture coords
                0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
                0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
        };
        vbo = Mn::Vbo::FromData(vertices);

        std::vector<unsigned int> indices{
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
        };
        ebo = Mn::Ebo::FromData(indices);

        // position attribute
        vao.Connect(0, 3, 8, 0);
        // color attribute
        vao.Connect(1, 3, 8, 3);
        // texture coord attribute
        vao.Connect(2, 2, 8, 6);

        // load and create a texture
        tex1 = Mn::Texture::FromImage("images/container.jpg");
        tex2 = Mn::Texture::FromImage("images/awesomeface.png");
    }

    ~TexturedRectangle() {
        shader.Release();
        tex1.Release();
        tex2.Release();
        vbo.Release();
        ebo.Release();
        vao.Release();
    }

    void Update(const Mn::Input &input) {
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        if (input.IsPressedKey(MN_KEY_UP)) {
            mixValue += 0.01f;
        }
        if (input.IsPressedKey(MN_KEY_DOWN)) {
            mixValue -= 0.01f;
        }
        if (mixValue > 1.0f) mixValue = 1.0f;
        if (mixValue < 0.0f) mixValue = 0.0f;

        mixValueUniform = mixValue;
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT);

        tex1.Activate(0);
        tex2.Activate(1);

        shader.Use();
        texture1Uniform.Upload();
        texture2Uniform.Upload();
        mixValueUniform.Upload();

        vao.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Ebo ebo{};
    Mn::Vao vao{};
    Mn::Uniform texture1Uniform{};
    Mn::Uniform texture2Uniform{};
    Mn::Uniform mixValueUniform{};
    float mixValue{0.2f};
    Mn::Texture tex1{};
    Mn::Texture tex2{};

    bool runScene{true};
};

int main() {
    Mn::Window wnd(800, 600, "Hello Texture");
    Mn::ShowScene<TexturedRectangle>(wnd);
    return 0;
}
