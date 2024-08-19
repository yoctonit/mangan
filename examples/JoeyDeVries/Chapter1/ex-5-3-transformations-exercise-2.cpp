#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Ebo.h"
#include "graphics/Vao.h"
#include "graphics/Uniform.h"
#include "graphics/Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class TransformationsExample {
public:
    TransformationsExample() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader = Mn::Shader::FromFiles(
                "shader/transform.vs",
                "shader/transform.fs"
        );
        texture1Uniform.Create(shader.Locate("texture1"), Mn::Uniform::Type::Int);
        texture1Uniform = 0;
        texture2Uniform.Create(shader.Locate("texture2"), Mn::Uniform::Type::Int);
        texture2Uniform = 1;
        transform1Uniform.Create(shader.Locate("transform"), Mn::Uniform::Type::Mat4x4);
        transform2Uniform.Create(shader.Locate("transform"), Mn::Uniform::Type::Mat4x4);

        vao.Create();

        std::vector<float> vertices{
                // positions         // texture coords
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // top left
        };
        vbo = Mn::Vbo::FromData(vertices);

        std::vector<unsigned int> indices{
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
        };
        ebo = Mn::Ebo::FromData(indices);

        // position attribute
        vao.Connect(0, 3, 5, 0);
        // texture coord attribute
        vao.Connect(1, 2, 5, 3);

        // load and create a texture
        tex1 = Mn::Texture::FromImage("images/container.jpg");
        tex2 = Mn::Texture::FromImage("images/awesomeface.png");
    }

    ~TransformationsExample() {
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

        time += 0.01f;

        auto transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, time, glm::vec3(0.0f, 0.0f, 1.0f));
        transform1Uniform = transform;

        transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
        float s = std::sin(time);
        transform = glm::scale(transform, glm::vec3(s, s, s));
        transform2Uniform = transform;
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

        transform1Uniform.Upload();
        vao.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        transform2Uniform.Upload();
        vao.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Ebo ebo{};
    Mn::Vao vao{};
    Mn::Uniform texture1Uniform{};
    Mn::Uniform texture2Uniform{};
    Mn::Uniform transform1Uniform{};
    Mn::Uniform transform2Uniform{};
    Mn::Texture tex1{};
    Mn::Texture tex2{};

    float time{};
    bool runScene{true};
};

int main() {
    Mn::Window wnd(800, 600, "Hello Texture");
    Mn::ShowScene<TransformationsExample>(wnd);
    return 0;
}
