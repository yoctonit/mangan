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


class Test_5_08 : public Base {
public:
    void initialize() override {
        Renderer::initialize();

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.0f, 1.5f, 5.0f));

        m_rig = std::make_shared<MovementRig>();
        m_rig->attach(m_camera);
        m_scene->add(m_rig);

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

        Texture labelTexture("images/crate-label.png");
        auto labelMaterial = std::make_shared<TextureMaterial>(labelTexture);
        std::shared_ptr<Geometry> labelGeometry = std::make_shared<RectangleGeometry>(1.0f, 0.5f);
        labelGeometry->applyMatrix(glm::rotate(-3.14f, glm::vec3(0.0f, 1.0f, 0.0f)));
        m_label = std::make_shared<Mesh>("label", labelGeometry, labelMaterial);
        // m_label->setPosition(glm::vec3(0.0f, 1.5f, 0.0f));
        m_label->applyMatrix(glm::translate(glm::vec3(0.0f, 1.5f, 0.0f)), true);
        m_scene->add(m_label);
    }

    void update() override {
        // note: looking at camera is similar to but
        // not precisely same effect as billboarding
        // not working (yet)
        // m_label->lookAt(m_camera->getPosition());

        m_rig->update(m_input, m_deltaTimeSeconds);
        Renderer::render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<MovementRig> m_rig;
    std::shared_ptr<Mesh> m_label;
};

int main() {
    Test_5_08().run();
    return 0;
}
