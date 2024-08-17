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
                "shader/texture.fs"
        );
        textureUniform.Create(shader.Locate("texture1"), Mn::Uniform::Type::Int); // default 0

        vao.Create();

        std::vector<float> vertices{
                // positions         // colors           // texture coords
                0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
                0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
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
        tex = Mn::Texture::FromImage("images/container.jpg");
    }

    ~TexturedRectangle() {
        shader.Release();
        tex.Release();
        vbo.Release();
        ebo.Release();
        vao.Release();
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        tex.Activate(0);

        // render container
        shader.Use();
        // textureUniform.Upload(); // no need to upload because default uniform value is 0
        vao.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Ebo ebo{};
    Mn::Vao vao{};
    Mn::Uniform textureUniform{};
    Mn::Texture tex{};
};

int main() {
    Mn::Window wnd(800, 600, "Hello Texture");
    Mn::ShowStaticScene<TexturedRectangle>(wnd);
    return 0;
}
