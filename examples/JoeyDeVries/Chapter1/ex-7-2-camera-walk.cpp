#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
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
        cubePositions = {
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(2.0f, 5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3(2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f, 3.0f, -7.5f),
                glm::vec3(1.3f, -2.0f, -2.5f),
                glm::vec3(1.5f, 2.0f, -2.5f),
                glm::vec3(1.5f, 0.2f, -1.5f),
                glm::vec3(-1.3f, 1.0f, -1.5f)
        };
        cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

        // configure global opengl state
        // -----------------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        shader = Mn::Shader::FromFiles(
                "shader/coordinate-systems.vs",
                "shader/texture-combined.fs"
        );
        texture1Uniform.Create(shader.Locate("texture1"), Mn::Uniform::Type::Int);
        texture1Uniform = 0;
        texture2Uniform.Create(shader.Locate("texture2"), Mn::Uniform::Type::Int);
        texture2Uniform = 1;
        for (unsigned int i = 0; i < 10; i++) {
            modelUniform.emplace_back(shader.Locate("model"), Mn::Uniform::Type::Mat4x4);
        }
        viewUniform.Create(shader.Locate("view"), Mn::Uniform::Type::Mat4x4);
        projectionUniform.Create(shader.Locate("projection"), Mn::Uniform::Type::Mat4x4);

        vao.Create();

        std::vector<float> vertices{
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
        };
        vbo = Mn::Vbo::FromData(vertices);

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
        vao.Release();
    }

    void Update(const Mn::Input &input) {
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        // per-frame time logic
        // --------------------
        time += 0.016f;
        deltaTime = time - lastFrame;
        lastFrame = time;
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;

        // create transformations
        auto cameraSpeed = 2.5f * deltaTime;
        if (input.IsPressedKey(MN_KEY_W)) {
            cameraPos += cameraSpeed * cameraFront;
        }
        if (input.IsPressedKey(MN_KEY_S)) {
            cameraPos -= cameraSpeed * cameraFront;
        }
        if (input.IsPressedKey(MN_KEY_A)) {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if (input.IsPressedKey(MN_KEY_D)) {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }

        auto view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        viewUniform = view;

        // note: currently we set the projection matrix each frame,
        // but since the projection matrix rarely changes
        // it's often best practice to set it outside the main loop only once.
        auto projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        projectionUniform = projection;

        for (unsigned int i = 0; i < 10; i++) {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (float) i;
            if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
                angle = time * 25.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            modelUniform[i] = model;
        }
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        // glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        tex1.Activate(0);
        tex2.Activate(1);

        shader.Use();
        texture1Uniform.Upload();
        texture2Uniform.Upload();

        viewUniform.Upload();
        projectionUniform.Upload();

        for (unsigned int i = 0; i < 10; i++) {
            modelUniform[i].Upload();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Vao vao{};
    Mn::Texture tex1{};
    Mn::Texture tex2{};

    Mn::Uniform texture1Uniform{};
    Mn::Uniform texture2Uniform{};
    Mn::Uniform viewUniform{};
    Mn::Uniform projectionUniform{};
    std::vector<Mn::Uniform> modelUniform;
    std::vector<glm::vec3> cubePositions;

    glm::vec3 cameraPos{};
    glm::vec3 cameraFront{};
    glm::vec3 cameraUp{};

    // timing
    float deltaTime{};	// time between current frame and last frame
    float lastFrame{};

    bool runScene{true};
    float time{};
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Hello Coordinate Systems");
    Mn::ShowScene<CoordinateSystems>(wnd);
    return 0;
}
