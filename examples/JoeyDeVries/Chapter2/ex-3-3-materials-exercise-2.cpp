#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Vao.h"
#include "graphics/Uniform.h"
#include "graphics/Texture.h"
#include "Camera.h"
#include "geometry/Icosahedron.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

std::vector<float> flatten(const std::vector<glm::vec3> &attributeList) {
    std::vector<float> data;
    for (auto &p: attributeList) {
        data.push_back(p.x);
        data.push_back(p.y);
        data.push_back(p.z);
    }
    return data;
}

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
    Mn::Vbo vbo1{};
    Mn::Vbo vbo2{};
    Mn::Vbo vbo3{};
    Mn::Vao cubeVao{};
    Mn::Vao lightCubeVao{};

    // uniforms for lightingShader
    Mn::Uniform modelUniform;
    Mn::Uniform viewUniform{};
    Mn::Uniform projectionUniform{};

    Mn::Uniform materialAmbientUniform;
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

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // lighting
    glm::vec3 lightPos{1.2f, 1.0f, 2.0f};
    int nv{};

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
                "shader/materials.fs"
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

        materialAmbientUniform.Create(
                lightingShader.Locate("material.ambient"),
                Mn::Uniform::Type::Vec3
        );
        materialDiffuseUniform.Create(
                lightingShader.Locate("material.diffuse"),
                Mn::Uniform::Type::Vec3
        );
        materialSpecularUniform.Create(
                lightingShader.Locate("material.specular"),
                Mn::Uniform::Type::Vec3
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

        Mn::Icosahedron icosahedron;
        icosahedron.Create(1.0f, 3);
        nv = icosahedron.numberOfVertices();
        vbo1 = Mn::Vbo::FromData(flatten(icosahedron.Vertices()));
        // position attribute
        cubeVao.Connect(0, 3, 3, 0);
        vbo2 = Mn::Vbo::FromData(flatten(icosahedron.Normals()));
        // normal attribute
        cubeVao.Connect(1, 3, 3, 0);

        lightCubeVao.Create();
        vbo3 = Mn::Vbo::FromData(cubeGeometry());
        lightCubeVao.Connect(0, 3, 6, 0);
    }

    ~LightSimpleColors() {
        lightingShader.Release();
        lightCubeShader.Release();
        cubeVao.Release();
        lightCubeVao.Release();
        vbo1.Release();
        vbo2.Release();
        vbo3.Release();
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

        // http://devernay.free.fr/cours/opengl/materials.html
        // cyan plastic
        materialAmbientUniform = glm::vec3(0.0f, 0.1f, 0.06f);
        materialDiffuseUniform = glm::vec3(0.0f, 0.50980392f, 0.50980392f);
        materialSpecularUniform = glm::vec3(0.50196078f, 0.50196078f, 0.50196078f);
        materialShininessUniform = 0.25f * 128.0f;

        // white rubber
//        materialAmbientUniform = glm::vec3(0.05f, 0.05f, 0.05f);
//        materialDiffuseUniform = glm::vec3(0.5f, 0.5f, 0.5f);
//        materialSpecularUniform = glm::vec3(0.7f, 0.7f, 0.7f);
//        materialShininessUniform = 0.78125f * 128.0f;

        lightPos.x = 1.0f + std::sin(time) * 2.0f;
        lightPos.y = std::sin(time / 2.0f) * 1.0f;
        lightPosUniform = lightPos;

        // note that all light colors are set at full intensity
        lightAmbientUniform = glm::vec3(1.0f, 1.0f, 1.0f);
        lightDiffuseUniform = glm::vec3(1.0f, 1.0f, 1.0f);
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

        materialAmbientUniform.Upload();
        materialDiffuseUniform.Upload();
        materialSpecularUniform.Upload();
        materialShininessUniform.Upload();

        lightPosUniform.Upload();
        lightAmbientUniform.Upload();
        lightDiffuseUniform.Upload();
        lightSpecularUniform.Upload();

        viewPosUniform.Upload();

        cubeVao.Draw(GL_TRIANGLES, 0, nv);

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
