#include "engine/Run.h"
#include "Camera.h"
#include "geometry/Icosahedron.h"
#include "geometry/Box.h"
#include "geometry/Plane.h"
#include "geometry/Polygon.h"
#include "geometry/Rectangle.h"
#include "geometry/Ellipsoid.h"
#include "geometry/Sphere.h"
#include "graphics/Material.h"
#include "graphics/Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;


class ExampleMeshes {
private:
    Mn::Mesh mPlane{};
    Mn::Mesh mObject{};
    Mn::Mesh mLightBulb{};

    Camera mCamera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // lighting
    glm::vec3 mLightPosition{1.2f, 1.0f, 2.0f};

    // timing
    float mTime{};
    float mDeltaTime{};    // mTime between current frame and last frame
    float mPreviousTime{};

    bool runScene{true};

public:
    ExampleMeshes() {
        // configure global opengl state
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        // create mesh mPlane
        Mn::Plane planeGeometry(10.0f, 10.f);
        auto transform = glm::rotate(glm::mat4(1.0f), -3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        planeGeometry.ApplyMatrix(transform);
        mPlane.Create(planeGeometry, Mn::Geometry::Type::PositionsAndNormals, Mn::BasicLightingMaterial());
        mPlane.renderSettings.Set(Mn::RenderSettings::Type::DoubleSide, true);

        // create mesh mObject
        Mn::Ellipsoid objectGeometry(2.0, 0.5f, 0.5f, 16, 16);
        objectGeometry.ApplyMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 0.0f)));
        mObject.Create(objectGeometry, Mn::Geometry::Type::PositionsAndNormals, Mn::BasicLightingMaterial());
        // mObject.renderSettings.Set(Mn::RenderSettings::Type::Wireframe, true);

        // create mesh mLightBulb
        mLightBulb.Create(
                Mn::Box(0.05f, 0.05f, 0.05f),
                Mn::Geometry::Type::Positions,
                Mn::BasicMvpColorMaterial()
        );
        mLightBulb.material["uColor"] = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    ~ExampleMeshes() {
        mPlane.Release();
        mObject.Release();
        mLightBulb.Release();
    }

    void Update(const Mn::Input &input) {
        // per-frame mTime logic
        mTime += 0.016f;
        mDeltaTime = mTime - mPreviousTime;
        mPreviousTime = mTime;

        // update light position
        mLightPosition.x = 1.0f + std::sin(mTime) * 2.0f;
        mLightPosition.y = std::sin(mTime / 2.0f) * 1.0f;

        ProcessInput(input);

        auto model = glm::mat4(1.0f);
        auto view = mCamera.GetViewMatrix();
        auto projection = glm::perspective(
                glm::radians(mCamera.Zoom),
                (float) SCR_WIDTH / (float) SCR_HEIGHT,
                0.1f, 100.0f
        );

        // mPlane transformations
        mPlane.material["uModel"] = model;
        mPlane.material["uView"] = view;
        mPlane.material["uProjection"] = projection;

        // mPlane material and lighting
        // white rubber (http://devernay.free.fr/cours/opengl/materials.html)
        mPlane.material["uMaterial.ambient"] = glm::vec3(0.05f, 0.05f, 0.05f);
        mPlane.material["uMaterial.diffuse"] = glm::vec3(0.5f, 0.5f, 0.5f);
        mPlane.material["uMaterial.specular"] = glm::vec3(0.7f, 0.7f, 0.7f);
        mPlane.material["uMaterial.shininess"] = 0.78125f * 128.0f;

        mPlane.material["uLight.position"] = mLightPosition;
        // note that all light colors are set at full intensity
        mPlane.material["uLight.ambient"] = glm::vec3(1.0f, 1.0f, 1.0f);
        mPlane.material["uLight.diffuse"] = glm::vec3(1.0f, 1.0f, 1.0f);
        mPlane.material["uLight.specular"] = glm::vec3(1.0f, 1.0f, 1.0f);

        mPlane.material["uViewPosition"] = mCamera.Position;

        // mObject transformations
        mObject.material["uModel"] = model;
        mObject.material["uView"] = view;
        mObject.material["uProjection"] = projection;

        // mObject material and lighting
        // cyan plastic (http://devernay.free.fr/cours/opengl/materials.html)
        mObject.material["uMaterial.ambient"] = glm::vec3(0.0f, 0.1f, 0.06f);
        mObject.material["uMaterial.diffuse"] = glm::vec3(0.0f, 0.50980392f, 0.50980392f);
        mObject.material["uMaterial.specular"] = glm::vec3(0.50196078f, 0.50196078f, 0.50196078f);
        mObject.material["uMaterial.shininess"] = 0.25f * 128.0f;

        mObject.material["uLight.position"] = mLightPosition;
        // note that all light colors are set at full intensity
        mObject.material["uLight.ambient"] = glm::vec3(1.0f, 1.0f, 1.0f);
        mObject.material["uLight.diffuse"] = glm::vec3(1.0f, 1.0f, 1.0f);
        mObject.material["uLight.specular"] = glm::vec3(1.0f, 1.0f, 1.0f);

        mObject.material["uViewPosition"] = mCamera.Position;

        // mLightBulb transformations
        mLightBulb.material["uModel"] = glm::translate(glm::mat4(1.0f), mLightPosition);
        mLightBulb.material["uView"] = view;
        mLightBulb.material["uProjection"] = projection;
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mPlane.Draw();
        mObject.Draw();
        mLightBulb.Draw();
    }

private:
    void ProcessInput(const Mn::Input &input) {
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        if (input.IsPressedKey(MN_KEY_W)) {
            mCamera.ProcessKeyboard(Camera::Movement::Forward, mDeltaTime);
        }
        if (input.IsPressedKey(MN_KEY_S)) {
            mCamera.ProcessKeyboard(Camera::Movement::Backward, mDeltaTime);
        }
        if (input.IsPressedKey(MN_KEY_A)) {
            mCamera.ProcessKeyboard(Camera::Movement::Left, mDeltaTime);
        }
        if (input.IsPressedKey(MN_KEY_D)) {
            mCamera.ProcessKeyboard(Camera::Movement::Right, mDeltaTime);
        }
        if (input.IsPressedKey(MN_KEY_R)) {
            mCamera.Position.y += 0.01f;
        }
        if (input.IsPressedKey(MN_KEY_F)) {
            mCamera.Position.y -= 0.01f;
        }

        auto mouseOffset = input.GetMouseOffset();
        mCamera.ProcessMouseMovement(mouseOffset.x, mouseOffset.y);

        auto scrollOffset = input.GetMouseScroll();
        mCamera.ProcessMouseScroll(scrollOffset.y);
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Meshes Example");
    wnd.CaptureCursor();
    Mn::ShowScene<ExampleMeshes>(wnd);
    return 0;
}
