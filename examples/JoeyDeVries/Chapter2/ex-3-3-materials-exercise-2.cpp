#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Vao.h"
#include "graphics/Uniform.h"
#include "graphics/Texture.h"
#include "Camera.h"
#include "geometry/Icosahedron.h"
#include "geometry/Box.h"
#include "geometry/Plane.h"
#include "material/BasicMvpColor.h"
#include "material/BasicLighting.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;


class LightSimpleColors {
private:
    Mn::Vao objectVao{};
    Mn::Vbo objectVbo{};
    Mn::BasicLighting objectMaterial{};

    Mn::Vao lightCubeVao{};
    Mn::Vbo lightCubeVbo{};
    Mn::BasicMvpColor lightCubeMaterial;

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

        objectMaterial.Create();

        lightCubeMaterial.Create();
//        lightCubeMaterial.GetUniform("uColor") = glm::vec3(1.0f, 1.0f, 1.0f);
        lightCubeMaterial["uColor"] = glm::vec3(1.0f, 1.0f, 1.0f);

        Mn::Plane plane(10.0f, 10.f);
        auto transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, -0.9f, 0.0f));
        transform = glm::rotate(transform, -3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        plane.ApplyMatrix(transform);

        Mn::Icosahedron icosahedron;
        icosahedron.Merge(plane);
        nv = icosahedron.VertexCount();

        objectVao.Create();
        objectVbo = Mn::Vbo::FromData(icosahedron.Data(Mn::Geometry::Type::PositionsAndNormals));
        objectVao.Connect(0, 3, 6, 0); // position attribute
        objectVao.Connect(1, 3, 6, 3); // normal attribute

        lightCubeVao.Create();
        lightCubeVbo = Mn::Vbo::FromData(Mn::Box(0.1f, 0.1f, 0.1f).Data(Mn::Geometry::Type::Positions));
        lightCubeVao.Connect(0, 3, 3, 0);
    }

    ~LightSimpleColors() {
        objectMaterial.Release();
        objectVao.Release();
        objectVbo.Release();

        lightCubeMaterial.Release();
        lightCubeVao.Release();
        lightCubeVbo.Release();
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
        objectMaterial.GetUniform("uModel") = model;

        // light model
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        // model = glm::scale(model, glm::vec3(0.1f)); // a smaller cube
//        lightCubeMaterial.GetUniform("uModel") = model;
        lightCubeMaterial["uModel"] = model;

        auto view = camera.GetViewMatrix();
        objectMaterial.GetUniform("uView") = view;
        lightCubeMaterial.GetUniform("uView") = view;

        auto projection = glm::perspective(
                glm::radians(camera.Zoom),
                (float) SCR_WIDTH / (float) SCR_HEIGHT,
                0.1f, 100.0f);
        objectMaterial.GetUniform("uProjection") = projection;
        lightCubeMaterial.GetUniform("uProjection") = projection;

        // http://devernay.free.fr/cours/opengl/materials.html
        // cyan plastic
        objectMaterial.GetUniform("uMaterial.ambient") = glm::vec3(0.0f, 0.1f, 0.06f);
        objectMaterial.GetUniform("uMaterial.diffuse") = glm::vec3(0.0f, 0.50980392f, 0.50980392f);
        objectMaterial.GetUniform("uMaterial.specular") = glm::vec3(0.50196078f, 0.50196078f, 0.50196078f);
        objectMaterial.GetUniform("uMaterial.shininess") = 0.25f * 128.0f;

        lightPos.x = 1.0f + std::sin(time) * 2.0f;
        lightPos.y = std::sin(time / 2.0f) * 1.0f;
        objectMaterial.GetUniform("uLight.position") = lightPos;

        // note that all light colors are set at full intensity
        objectMaterial.GetUniform("uLight.ambient") = glm::vec3(1.0f, 1.0f, 1.0f);
        objectMaterial.GetUniform("uLight.diffuse") = glm::vec3(1.0f, 1.0f, 1.0f);
        objectMaterial.GetUniform("uLight.specular") = glm::vec3(1.0f, 1.0f, 1.0f);

        objectMaterial.GetUniform("uViewPosition") = camera.Position;
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        objectMaterial.Upload();
        objectVao.Draw(GL_TRIANGLES, 0, nv);

        lightCubeMaterial.Upload();
        lightCubeVao.Draw(GL_TRIANGLES, 0, 36);
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<LightSimpleColors>(wnd);
    return 0;
}
