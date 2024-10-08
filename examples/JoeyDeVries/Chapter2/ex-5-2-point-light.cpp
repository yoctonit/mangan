#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Vao.h"
#include "graphics/Uniform.h"
#include "graphics/Texture.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

class CoordinateSystems {
private:
    Mn::Shader shader{};
    Mn::Shader lightCubeShader{};
    Mn::Vbo vbo{};
    Mn::Vao vao{};
    Mn::Vao lightCubeVao{};

    Mn::Uniform viewUniform{};
    Mn::Uniform projectionUniform{};
    std::vector<Mn::Uniform> modelUniform;

    Mn::Uniform materialDiffuseUniform{};
    Mn::Uniform materialSpecularUniform{};
    Mn::Uniform materialShininessUniform{};

    Mn::Uniform lightPositionUniform{};
    Mn::Uniform lightAmbientUniform{};
    Mn::Uniform lightDiffuseUniform{};
    Mn::Uniform lightSpecularUniform{};
    Mn::Uniform lightConstantUniform{};
    Mn::Uniform lightLinearUniform{};
    Mn::Uniform lightQuadraticUniform{};

    Mn::Uniform viewPosUniform{};

    // uniforms for lightCubeShader
    Mn::Uniform lightModelUniform;
    Mn::Uniform lightViewUniform{};
    Mn::Uniform lightProjectionUniform{};

    Mn::Texture tex1{};
    Mn::Texture tex2{};

    // lighting
    glm::vec3 lightPos{1.2f, 1.0f, 2.0f};
    
    std::vector<glm::vec3> cubePositions;

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    bool runScene{true};

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

        // configure global opengl state
        // -----------------------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        shader = Mn::Shader::FromFiles(
                "shader/lighting_maps_1.vs",
                "shader/point_light.fs"
        );

        for (unsigned int i = 0; i < 10; i++) {
            modelUniform.emplace_back(shader.Locate("model"), Mn::Uniform::Type::Mat4x4);
        }
        viewUniform.Create(shader.Locate("view"), Mn::Uniform::Type::Mat4x4);
        projectionUniform.Create(shader.Locate("projection"), Mn::Uniform::Type::Mat4x4);

        materialDiffuseUniform.Create(shader.Locate("material.diffuse"), Mn::Uniform::Type::Int);
        materialDiffuseUniform = 0;
        materialSpecularUniform.Create(shader.Locate("material.specular"), Mn::Uniform::Type::Int);
        materialSpecularUniform = 1;
        materialShininessUniform.Create(shader.Locate("material.shininess"), Mn::Uniform::Type::Float);

        lightPositionUniform.Create(shader.Locate("light.position"), Mn::Uniform::Type::Vec3);
        lightAmbientUniform.Create(shader.Locate("light.ambient"), Mn::Uniform::Type::Vec3);
        lightDiffuseUniform.Create(shader.Locate("light.diffuse"), Mn::Uniform::Type::Vec3);
        lightSpecularUniform.Create(shader.Locate("light.specular"), Mn::Uniform::Type::Vec3);
        lightConstantUniform.Create(shader.Locate("light.constant"), Mn::Uniform::Type::Float);
        lightLinearUniform.Create(shader.Locate("light.linear"), Mn::Uniform::Type::Float);
        lightQuadraticUniform.Create(shader.Locate("light.quadratic"), Mn::Uniform::Type::Float);

        viewPosUniform.Create(shader.Locate("viewPos"), Mn::Uniform::Type::Vec3);

        lightCubeShader = Mn::Shader::FromFiles(
                "shader/colors.vs",
                "shader/light_cube.fs"
        );
        lightModelUniform.Create(
                lightCubeShader.Locate("model"),
                Mn::Uniform::Type::Mat4x4
        );
        lightViewUniform.Create(
                lightCubeShader.Locate("view"),
                Mn::Uniform::Type::Mat4x4
        );
        lightProjectionUniform.Create(
                lightCubeShader.Locate("projection"),
                Mn::Uniform::Type::Mat4x4
        );

        vao.Create();

        std::vector<float> vertices{
                // positions          // normals           // texture coords
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

                -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
        };
        vbo = Mn::Vbo::FromData(vertices);

        // position attribute
        vao.Connect(0, 3, 8, 0);
        // normal attribute
        vao.Connect(1, 3, 8, 3);
        // texture coord attribute
        vao.Connect(2, 2, 8, 6);

        lightCubeVao.Create();
        // position attribute (buffer still bound)
        lightCubeVao.Connect(0, 3, 8, 0);

        // load and create a texture
        tex1 = Mn::Texture::FromImage("images/container2.png");
        tex2 = Mn::Texture::FromImage("images/container2_specular.png");
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

        // create transformations
        if (input.IsPressedKey(MN_KEY_W)) {
            camera.ProcessKeyboard(Camera::Movement::Forward, deltaTime);
        }
        if (input.IsPressedKey(MN_KEY_S)) {
            camera.ProcessKeyboard(Camera::Movement::Backward, deltaTime);
        }
        if (input.IsPressedKey(MN_KEY_A)) {
            camera.ProcessKeyboard(Camera::Movement::Left, deltaTime);
        }
        if (input.IsPressedKey(MN_KEY_D)) {
            camera.ProcessKeyboard(Camera::Movement::Right, deltaTime);
        }

        auto mouseOffset = input.GetMouseOffset();
        camera.ProcessMouseMovement(mouseOffset.x, mouseOffset.y);

        auto scrollOffset = input.GetMouseScroll();
        camera.ProcessMouseScroll(scrollOffset.y);

        materialShininessUniform = 32.0f;

        lightPositionUniform = lightPos;
        lightAmbientUniform = glm::vec3(0.2f, 0.2f, 0.2f);
        lightDiffuseUniform = glm::vec3(0.5f, 0.5f, 0.5f);
        lightSpecularUniform = glm::vec3(1.0f, 1.0f, 1.0f);
        lightConstantUniform = 1.0f;
        lightLinearUniform = 0.09f;
        lightQuadraticUniform = 0.032f;

        viewPosUniform = camera.Position;

        auto view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        viewUniform = view;
        lightViewUniform = view;

        // note: currently we set the projection matrix each frame,
        // but since the projection matrix rarely changes
        // it's often best practice to set it outside the main loop only once.
        auto projection = glm::mat4(1.0f);
        projection = glm::perspective(
                glm::radians(camera.Zoom),
                (float) SCR_WIDTH / (float) SCR_HEIGHT,
                0.1f, 100.0f);
        projectionUniform = projection;
        lightProjectionUniform = projection;

        for (unsigned int i = 0; i < 10; i++) {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (float) i;
            if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
                angle = time * 25.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            modelUniform[i] = model;
        }

        {
            // light model
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
            lightModelUniform = model;
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
        viewUniform.Upload();
        projectionUniform.Upload();

        materialDiffuseUniform.Upload();
        materialSpecularUniform.Upload();
        materialShininessUniform.Upload();

        lightPositionUniform.Upload();
        lightAmbientUniform.Upload();
        lightDiffuseUniform.Upload();
        lightSpecularUniform.Upload();
        lightConstantUniform.Upload();
        lightLinearUniform.Upload();
        lightQuadraticUniform.Upload();

        viewPosUniform.Upload();

        for (unsigned int i = 0; i < 10; i++) {
            modelUniform[i].Upload();
            vao.Draw(GL_TRIANGLES, 0, 36);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        lightCubeShader.Use();
        lightModelUniform.Upload();
        lightViewUniform.Upload();
        lightProjectionUniform.Upload();

        lightCubeVao.Draw(GL_TRIANGLES, 0, 36);

    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<CoordinateSystems>(wnd);
    return 0;
}
