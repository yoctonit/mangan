#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "geometry/BoxGeometry.h"
#include "geometry/RectangleGeometry.h"
#include "material/TextureMaterial.h"
#include "extras/MovementRig.h"
#include "extras/GridHelper.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/transform.hpp"


class Test_5_10 : public Base {
public:
    void initialize() override {
        m_renderer = std::make_shared<Renderer>();

        m_scene = std::make_shared<Object3D>("scene");

        // for non-square windows, adjust aspect ratio size
        m_camera = std::make_shared<Camera>(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
        m_camera->setPosition(glm::vec3(0.0f, 1.5f, 5.0f));

        m_rig = std::make_shared<MovementRig>();
        m_rig->attach(m_camera);
        m_scene->add(m_rig);

        // main scene
        std::shared_ptr<Geometry> boxGeometry = std::make_shared<BoxGeometry>();
        Texture crate("images/crate.png");
        auto boxMaterial = std::make_shared<TextureMaterial>(crate);
        auto box = std::make_shared<Mesh>("box", boxGeometry, boxMaterial);
        // box->setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
        box->applyMatrix(glm::translate(glm::vec3(0.0f, 0.5f, 0.0f)), true);
        m_scene->add(box);

        auto grid = std::make_shared<GridHelper>(
                10.0f, 10.0f,
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(1.0f, 0.5f, 0.5f),
                2);
        grid->rotateX(-3.14f / 2.0f, true);
        m_scene->add(grid);

        // HUD scene
        m_hudScene = std::make_shared<Object3D>("HUD");
        m_hudCamera = std::make_shared<Camera>();
        m_hudCamera->setOrthographic(0.0f, 800.0f, 0.0f, 600.0f, 1.0f, -1.0f);

        std::shared_ptr<Geometry> labelGeo1 = std::make_shared<RectangleGeometry>(600.0f, 80.0f,
                                                                                  glm::vec2(0.0f, 600.0f),
                                                                                  glm::vec2(0.0f, 1.0f));
        Texture labelTex1("images/crate-sim.png");
        auto labelMat1 = std::make_shared<TextureMaterial>(labelTex1);
        auto label1 = std::make_shared<Mesh>("label1", labelGeo1, labelMat1);
        m_hudScene->add(label1);

        std::shared_ptr<Geometry> labelGeo2 = std::make_shared<RectangleGeometry>(400.0f, 80.0f,
                                                                                  glm::vec2(800.0f, 0.0f),
                                                                                  glm::vec2(1.0f, 0.0f));
        Texture labelTex2("images/version-1.png");
        auto labelMat2 = std::make_shared<TextureMaterial>(labelTex2);
        auto label2 = std::make_shared<Mesh>("label2", labelGeo2, labelMat2);
        m_hudScene->add(label2);
    }

    void update() override {
        m_rig->update(m_input, m_deltaTimeSeconds);
        m_renderer->clearColorBuffer = true;
        m_renderer->render(m_scene, m_camera);
        m_renderer->clearColorBuffer = false;
        m_renderer->render(m_hudScene, m_hudCamera);
    }

private:
    std::shared_ptr<Renderer> m_renderer{};
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Object3D> m_hudScene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Camera> m_hudCamera{};
    std::shared_ptr<MovementRig> m_rig;
    std::shared_ptr<Mesh> m_label;
};

int main() {
    Test_5_10().run(800, 600, "HUD Example");
    return 0;
}
