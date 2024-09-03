#include "engine/Run.h"
#include "Camera.h"
#include "geometry/Icosahedron.h"
#include "geometry/Box.h"
#include "geometry/Plane.h"
#include "geometry/Polygon.h"
#include "geometry/Rectangle.h"
#include "geometry/Ellipsoid.h"
#include "graphics/Material.h"
#include "graphics/Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;


class ExampleMeshes {
private:
    Mn::Mesh object{};
    Mn::Mesh lightCube{};

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // lighting
    glm::vec3 lightPos{1.2f, 1.0f, 2.0f};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    bool runScene{true};

public:
    ExampleMeshes() {
        // configure global opengl state
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        // create mesh objects
        Mn::Plane plane(10.0f, 10.f);
        auto transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, -0.9f, 0.0f));
        transform = glm::rotate(transform, -3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        plane.ApplyMatrix(transform);

        Mn::Polygon polygon(3, 2.0f);
//        transform = glm::mat4(1.0f);
//        transform = glm::rotate(transform, -3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
//        polygon.ApplyMatrix(transform);

        Mn::Rectangle rectangle(0.2f, 5.0f);
        rectangle.ApplyMatrix(glm::rotate(glm::mat4(1.0f), -3.14f / 4.0f, glm::vec3(0.0f, 0.0f, -1.0f)));

        Mn::Ellipsoid ellipsoid(2.0, 0.5f, 0.5f, 64, 64);
//        Mn::Ellipsoid ellipsoid;
        ellipsoid.ApplyMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 0.0f)));

        Mn::Icosahedron icosahedron;
        icosahedron.Merge(plane);
        icosahedron.Merge(polygon);
        icosahedron.Merge(rectangle);
        icosahedron.Merge(ellipsoid);

        object.Create(icosahedron, Mn::Geometry::Type::PositionsAndNormals, Mn::BasicLightingMaterial());

        lightCube.Create(
                Mn::Box(0.05f, 0.05f, 0.05f),
                Mn::Geometry::Type::Positions,
                Mn::BasicMvpColorMaterial()
        );
        lightCube.material["uColor"] = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    ~ExampleMeshes() {
        object.Release();
        lightCube.Release();
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
        object.material["uModel"] = model;

        // light model
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        // model = glm::scale(model, glm::vec3(0.1f)); // a smaller cube
        lightCube.material["uModel"] = model;

        auto view = camera.GetViewMatrix();
        object.material["uView"] = view;
        lightCube.material["uView"] = view;

        auto projection = glm::perspective(
                glm::radians(camera.Zoom),
                (float) SCR_WIDTH / (float) SCR_HEIGHT,
                0.1f, 100.0f);
        object.material["uProjection"] = projection;
        lightCube.material["uProjection"] = projection;

        // http://devernay.free.fr/cours/opengl/materials.html
        // cyan plastic
        object.material["uMaterial.ambient"] = glm::vec3(0.0f, 0.1f, 0.06f);
        object.material["uMaterial.diffuse"] = glm::vec3(0.0f, 0.50980392f, 0.50980392f);
        object.material["uMaterial.specular"] = glm::vec3(0.50196078f, 0.50196078f, 0.50196078f);
        object.material["uMaterial.shininess"] = 0.25f * 128.0f;

        lightPos.x = 1.0f + std::sin(time) * 2.0f;
        lightPos.y = std::sin(time / 2.0f) * 1.0f;
        object.material["uLight.position"] = lightPos;

        // note that all light colors are set at full intensity
        object.material["uLight.ambient"] = glm::vec3(1.0f, 1.0f, 1.0f);
        object.material["uLight.diffuse"] = glm::vec3(1.0f, 1.0f, 1.0f);
        object.material["uLight.specular"] = glm::vec3(1.0f, 1.0f, 1.0f);

        object.material["uViewPosition"] = camera.Position;
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        object.Draw();
        lightCube.Draw();
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Meshes Example");
    wnd.CaptureCursor();
    Mn::ShowScene<ExampleMeshes>(wnd);
    return 0;
}
