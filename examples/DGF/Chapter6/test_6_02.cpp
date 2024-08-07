#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/RenderTarget.h"
#include "core/Mesh.h"
#include "geometry/RectangleGeometry.h"
#include "material/LambertMaterial.h"
#include "light/AmbientLight.h"
#include "light/DirectionalLight.h"
#include "light/PointLight.h"
#include "extras/MovementRig.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/transform.hpp"


class Test_6_02 : public Base {
public:
    void initialize() override {
        m_renderer = std::make_shared<Renderer>();
        m_renderer->setDimensions(1600, 1200);
        m_renderer->setClearColor(glm::vec3(0.2f, 0.2f, 0.2f));

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPerspective(60.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
        m_camera->setPosition(glm::vec3(0.0f, 0.0f, 2.5f));

        m_rig = std::make_shared<MovementRig>();
        m_rig->attach(m_camera);
        m_scene->add(m_rig);

        m_renderer->light0 = std::make_shared<AmbientLight>(glm::vec3(0.3f, 0.3f, 0.3f));

//        m_renderer->light1 = std::make_shared<DirectionalLight>(
//                glm::vec3(0.8f, 0.8f, 0.8f),
//                glm::vec3(-1.0f, -1.0f, -2.0f)
//        );

        m_renderer->light1 = std::make_shared<PointLight>(
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(1.2f, 1.2f, 0.3f)
        );

        std::shared_ptr<Geometry> geometry = std::make_shared<RectangleGeometry>(2.0f, 2.0f);

        auto brickColor = std::make_shared<Texture>("images/brick-color.png");
        auto bumpMaterial = std::make_shared<LambertMaterial>(brickColor);
        auto brickBump = std::make_shared<Texture>("images/brick-bump.png");
        bumpMaterial->addBumpData(brickBump, 1.5f);

        auto mesh = std::make_shared<Mesh>("rectangle", geometry, bumpMaterial);
        m_scene->add(mesh);
    }

    void update() override {
        m_rig->update(m_input, m_deltaTimeSeconds);
        m_renderer->render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Renderer> m_renderer{};
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<MovementRig> m_rig{};
};

int main() {
    Test_6_02().run(1600, 1200, "Bump Map Example");
    return 0;
}
