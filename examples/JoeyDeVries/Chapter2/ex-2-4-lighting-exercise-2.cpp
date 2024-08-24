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
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
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
    Mn::Uniform lightPosUniform;
    Mn::Uniform viewPosUniform;
    Mn::Uniform lightColorUniform;
    Mn::Uniform objectColorUniform;
    Mn::Uniform uAmbientStrength;
    Mn::Uniform uSpecularStrength;
    Mn::Uniform uShininess;
    float ambientStrength{0.1f};
    float specularStrength{0.5f};
    float shininess{32.0f};


    // uniforms for lightCubeShader
    Mn::Uniform lightModelUniform;
    Mn::Uniform lightViewUniform{};
    Mn::Uniform lightProjectionUniform{};

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // lighting
    // glm::vec3 lightPos{1.2f, 1.0f, 2.0f};
    glm::vec3 lightPos{0.2f, 0.2f, 2.0f};

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
                "shader/basic_lighting_specular.vs",
                "shader/exercise-2.fs"
        );
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
        lightPosUniform.Create(
                lightingShader.Locate("lightPos"),
                Mn::Uniform::Type::Vec3
        );
        lightPosUniform = lightPos;
        viewPosUniform.Create(
                lightingShader.Locate("viewPos"),
                Mn::Uniform::Type::Vec3
        );
        lightColorUniform.Create(
                lightingShader.Locate("lightColor"),
                Mn::Uniform::Type::Vec3
        );
        lightColorUniform = glm::vec3(1.0f, 1.0f, 1.0f);
        objectColorUniform.Create(
                lightingShader.Locate("objectColor"),
                Mn::Uniform::Type::Vec3
        );
        objectColorUniform = glm::vec3(1.0f, 0.5f, 0.31f);
        uAmbientStrength.Create(
                lightingShader.Locate("uAmbientStrength"),
                Mn::Uniform::Type::Float
        );
        uSpecularStrength.Create(
                lightingShader.Locate("uSpecularStrength"),
                Mn::Uniform::Type::Float
        );
        uShininess.Create(
                lightingShader.Locate("uShininess"),
                Mn::Uniform::Type::Float
        );

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

        cubeVao.Create();
        vbo = Mn::Vbo::FromData(cubeGeometry());

        // position attribute
        cubeVao.Connect(0, 3, 6, 0);
        // normal attribute
        cubeVao.Connect(1, 3, 6, 3);

        lightCubeVao.Create();
        // position attribute (buffer still bound)
        lightCubeVao.Connect(0, 3, 6, 0);
    }

    ~LightSimpleColors() {
        lightingShader.Release();
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

        if (input.IsClickedKey(MN_KEY_T)) {
            ambientStrength += 0.1f;
            if (ambientStrength > 1.0f) ambientStrength = 1.0f;
        }
        if (input.IsClickedKey(MN_KEY_G)) {
            ambientStrength -= 0.1f;
            if (ambientStrength < 0.0f) ambientStrength = 0.0f;
        }

        if (input.IsClickedKey(MN_KEY_Y)) {
            specularStrength += 0.1f;
            if (specularStrength > 1.0f) specularStrength = 1.0f;
        }
        if (input.IsClickedKey(MN_KEY_H)) {
            specularStrength -= 0.1f;
            if (specularStrength < 0.0f) specularStrength = 0.0f;
        }

        if (input.IsPressedKey(MN_KEY_U)) {
            shininess += 0.1f;
            if (shininess > 256.0f) shininess = 256.0f;
        }
        if (input.IsPressedKey(MN_KEY_J)) {
            shininess -= 0.1f;
            if (shininess < 2.0f) shininess = 2.0f;
        }

        auto mouseOffset = input.GetMouseOffset();
        camera.ProcessMouseMovement(mouseOffset.x, mouseOffset.y);

        auto scrollOffset = input.GetMouseScroll();
        camera.ProcessMouseScroll(scrollOffset.y);
        // -------------

        // view/projection transformations
        viewPosUniform = camera.Position;

        auto view = camera.GetViewMatrix();
        viewUniform = view;
        lightViewUniform = view;

        auto projection = glm::perspective(
                glm::radians(camera.Zoom),
                (float) SCR_WIDTH / (float) SCR_HEIGHT,
                0.1f, 100.0f);
        projectionUniform = projection;
        lightProjectionUniform = projection;

        // world transformation
        // object model
        auto model = glm::mat4(1.0f);
        modelUniform = model;

        // light model
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.1f)); // a smaller cube
        lightModelUniform = model;

        // change the light's position values over time
        // (can be done anywhere in the render loop actually,
        // but try to do it at least before using the light source positions)
        lightPos.x = 1.0f + std::sin(time) * 2.0f;
        lightPos.y = std::sin(time / 2.0f) * 1.0f;
        lightPosUniform = lightPos;

        uAmbientStrength = ambientStrength;
        uSpecularStrength = specularStrength;
        uShininess = shininess;
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
        lightPosUniform.Upload();
        viewPosUniform.Upload();
        lightColorUniform.Upload();
        objectColorUniform.Upload();
        uAmbientStrength.Upload();
        uSpecularStrength.Upload();
        uShininess.Upload();

        cubeVao.Draw(GL_TRIANGLES, 0, 36);

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
    Mn::ShowScene<LightSimpleColors>(wnd);
    return 0;
}
