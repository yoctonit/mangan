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

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

class CoordinateSystems {
public:
    CoordinateSystems() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader = Mn::Shader::FromFiles(
                "shader/coordinate-systems.vs",
                "shader/texture-combined.fs"
        );
        texture1Uniform.Create(shader.Locate("texture1"), Mn::Uniform::Type::Int);
        texture1Uniform = 0;
        texture2Uniform.Create(shader.Locate("texture2"), Mn::Uniform::Type::Int);
        texture2Uniform = 1;
        modelUniform.Create(shader.Locate("model"), Mn::Uniform::Type::Mat4x4);
        viewUniform.Create(shader.Locate("view"), Mn::Uniform::Type::Mat4x4);
        projectionUniform.Create(shader.Locate("projection"), Mn::Uniform::Type::Mat4x4);

        vao.Create();

        std::vector<float> vertices{
                // positions          // texture coords
                0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
                0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
                -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left
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

    ~CoordinateSystems() {
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

        // create transformations
        auto model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        auto view = glm::mat4(1.0f);
        auto projection = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // note: currently we set the projection matrix each frame,
        // but since the projection matrix rarely changes
        // it's often best practice to set it outside the main loop only once.
        projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);

        modelUniform = model;
        viewUniform = view;
        projectionUniform = projection;
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
        modelUniform.Upload();
        viewUniform.Upload();
        projectionUniform.Upload();

        vao.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Ebo ebo{};
    Mn::Vao vao{};
    Mn::Texture tex1{};
    Mn::Texture tex2{};

    Mn::Uniform texture1Uniform{};
    Mn::Uniform texture2Uniform{};
    Mn::Uniform modelUniform{};
    Mn::Uniform viewUniform{};
    Mn::Uniform projectionUniform{};

    bool runScene{true};
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Hello Coordinate Systems");
    Mn::ShowScene<CoordinateSystems>(wnd);
    return 0;
}
