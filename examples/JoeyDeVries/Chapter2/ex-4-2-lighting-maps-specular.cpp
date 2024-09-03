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

std::vector<float> cubeGeometry() {
    return {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
}


class LightSimpleColors {
private:
    Mn::Shader lightingShader{};
    Mn::Shader lightCubeShader{};
    Mn::Vbo vbo{};
    Mn::Vao cubeVao{};
    Mn::Vao lightCubeVao{};

    // uniforms for lightingShader
    Mn::Uniform modelUniform;
    Mn::Uniform viewUniform{};
    Mn::Uniform projectionUniform{};

    Mn::Uniform materialDiffuseUniform;
    Mn::Uniform materialSpecularUniform;
    Mn::Uniform materialShininessUniform;

    Mn::Uniform lightPosUniform;
    Mn::Uniform lightAmbientUniform;
    Mn::Uniform lightDiffuseUniform;
    Mn::Uniform lightSpecularUniform;

    Mn::Uniform viewPosUniform;

    // uniforms for lightCubeShader
    Mn::Uniform lightColorUniform;
    Mn::Uniform lightModelUniform;
    Mn::Uniform lightViewUniform{};
    Mn::Uniform lightProjectionUniform{};

    Mn::Texture diffuseMap {};
    Mn::Texture specularMap {};

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // lighting
    glm::vec3 lightPos{1.2f, 1.0f, 2.0f};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    bool runScene{true};

public:
    LightSimpleColors() {
        // configure global opengl state
        // -----------------------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        lightingShader = Mn::Shader::FromFiles(
                "shader/lighting_maps_1.vs",
                "shader/lighting_maps_specular.fs"
        );
        // uniforms for lightingShader
        modelUniform.Create(
                lightingShader.Locate("model"),
                Mn::Uniform::Type::Mat4x4
        );
        viewUniform.Create(
                lightingShader.Locate("view"),
                Mn::Uniform::Type::Mat4x4
        );
        projectionUniform.Create(
                lightingShader.Locate("projection"),
                Mn::Uniform::Type::Mat4x4
        );

        materialDiffuseUniform.Create(
                lightingShader.Locate("material.diffuse"),
                Mn::Uniform::Type::Int
        );
        materialSpecularUniform.Create(
                lightingShader.Locate("material.specular"),
                Mn::Uniform::Type::Int
        );
        materialShininessUniform.Create(
                lightingShader.Locate("material.shininess"),
                Mn::Uniform::Type::Float
        );

        lightPosUniform.Create(
                lightingShader.Locate("light.position"),
                Mn::Uniform::Type::Vec3
        );
        lightAmbientUniform.Create(
                lightingShader.Locate("light.ambient"),
                Mn::Uniform::Type::Vec3
        );
        lightDiffuseUniform.Create(
                lightingShader.Locate("light.diffuse"),
                Mn::Uniform::Type::Vec3
        );
        lightSpecularUniform.Create(
                lightingShader.Locate("light.specular"),
                Mn::Uniform::Type::Vec3
        );

        viewPosUniform.Create(
                lightingShader.Locate("viewPos"),
                Mn::Uniform::Type::Vec3
        );

        // uniforms for lightCubeShader
        lightCubeShader = Mn::Shader::FromFiles(
                "shader/colors.vs",
                "shader/light_cube_exercise_1.fs"
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
        lightColorUniform.Create(
                lightCubeShader.Locate("lightColor"),
                Mn::Uniform::Type::Vec3
        );
        lightColorUniform = glm::vec3(1.0f, 1.0f, 1.0f);

        cubeVao.Create();

        vbo = Mn::Vbo::FromData(cubeGeometry());
        // position attribute
        cubeVao.Connect(0, 3, 8, 0);
        // normal attribute
        cubeVao.Connect(1, 3, 8, 3);
        // texture attribute
        cubeVao.Connect(2, 2, 8, 6);

        lightCubeVao.Create();
        lightCubeVao.Connect(0, 3, 8, 0);

        diffuseMap = Mn::Texture::FromImage("images/container2.png");
        specularMap = Mn::Texture::FromImage("images/container2_specular.png");
    }

    ~LightSimpleColors() {
        lightingShader.Release();
        lightCubeShader.Release();
        cubeVao.Release();
        lightCubeVao.Release();
        vbo.Release();
    }

    void Update(const Mn::Input &input) {
        // per-frame time logic
        // --------------------
        time += 0.016f;
        deltaTime = time - lastFrame;
        lastFrame = time;

        // process input
        // -------------
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

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
        if (input.IsPressedKey(MN_KEY_R)) {
            camera.Position.y += 0.01f;
        }
        if (input.IsPressedKey(MN_KEY_F)) {
            camera.Position.y -= 0.01f;
        }

        auto mouseOffset = input.GetMouseOffset();
        camera.ProcessMouseMovement(mouseOffset.x, mouseOffset.y);

        auto scrollOffset = input.GetMouseScroll();
        camera.ProcessMouseScroll(scrollOffset.y);
        // -------------

        // world transformation
        // object model
        auto model = glm::mat4(1.0f);
        modelUniform = model;

        // light model
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.1f)); // a smaller cube
        lightModelUniform = model;

        auto view = camera.GetViewMatrix();
        viewUniform = view;
        lightViewUniform = view;

        auto projection = glm::perspective(
                glm::radians(camera.Zoom),
                (float) SCR_WIDTH / (float) SCR_HEIGHT,
                0.1f, 100.0f);
        projectionUniform = projection;
        lightProjectionUniform = projection;

        materialDiffuseUniform = 0;
        materialSpecularUniform = 1;
        materialShininessUniform = 64.0f;

        lightPos.x = 1.0f + std::sin(time) * 2.0f;
        lightPos.y = std::sin(time / 2.0f) * 1.0f;
        lightPosUniform = lightPos;

        lightAmbientUniform = glm::vec3(0.2f, 0.2f, 0.2f);
        lightDiffuseUniform = glm::vec3(0.5f, 0.5f, 0.5f);
        lightSpecularUniform = glm::vec3(1.0f, 1.0f, 1.0f);

        viewPosUniform = camera.Position;
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.Use();

        modelUniform.Upload();
        viewUniform.Upload();
        projectionUniform.Upload();

        materialDiffuseUniform.Upload();
        materialSpecularUniform.Upload();
        materialShininessUniform.Upload();

        lightPosUniform.Upload();
        lightAmbientUniform.Upload();
        lightDiffuseUniform.Upload();
        lightSpecularUniform.Upload();

        viewPosUniform.Upload();

        // bind diffuse and specular maps
        diffuseMap.Activate(0);
        specularMap.Activate(1);

        cubeVao.Draw(GL_TRIANGLES, 0, 36);

        lightCubeShader.Use();
        lightModelUniform.Upload();
        lightViewUniform.Upload();
        lightProjectionUniform.Upload();
        lightColorUniform.Upload();

        lightCubeVao.Draw(GL_TRIANGLES, 0, 36);
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<LightSimpleColors>(wnd);
    return 0;
}
