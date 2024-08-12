#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/RenderTarget.h"
#include "core/Mesh.h"
#include "geometry/RectangleGeometry.h"
#include "geometry/BoxGeometry.h"
#include "geometry/SphereGeometry.h"
#include "material/LambertMaterial.h"
#include "material/TextureMaterial.h"
#include "light/AmbientLight.h"
#include "light/DirectionalLight.h"
#include "light/PointLight.h"
#include "extras/MovementRig.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/transform.hpp"


class Test_6_05 : public Base {
public:
    void initialize() override {
        m_renderer = std::make_shared<Renderer>();
        m_renderer->setDimensions(800, 600);
        m_renderer->setClearColor(glm::vec3(0.25f, 0.25f, 0.25f));

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPerspective(60.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
        m_camera->setPosition(glm::vec3(0.0f, 3.0f, 6.0f));

        m_rig = std::make_shared<MovementRig>();
        m_rig->attach(m_camera);
        m_scene->add(m_rig);

        m_renderer->light0 = std::make_shared<AmbientLight>(glm::vec3(0.2f, 0.2f, 0.2f));

        m_directionalLight = std::make_shared<DirectionalLight>(
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(-1.0f, -1.0f, 0.0f)
        );
        m_renderer->light1 = m_directionalLight;


        std::shared_ptr<Geometry> geometry = std::make_shared<SphereGeometry>();
        auto grid = std::make_shared<Texture>("images/grid.png");
        auto shadowMaterial = std::make_shared<LambertMaterial>(grid);
        shadowMaterial->enableShadow();

        auto sphere1 = std::make_shared<Mesh>("sphere1", geometry, shadowMaterial);
        sphere1->applyMatrix(glm::translate(glm::vec3(-2.0f, 1.0f, 0.0f)), true);
        m_scene->add(sphere1);

        auto sphere2 = std::make_shared<Mesh>("sphere2", geometry, shadowMaterial);
        sphere2->applyMatrix(glm::translate(glm::vec3(1.0f, 2.2f, -0.5f)), true);
        m_scene->add(sphere2);

        m_renderer->enableShadows(m_directionalLight);

        // optional: render depth texture to mesh in scene.
        //  note: this object may also cast a shadow in scene.
//        auto depthTexture = m_renderer->shadowObject->renderTarget->texture;
//        auto shadowDisplay = std::make_shared<Mesh>(
//                "shadow-display",
//                std::make_shared<RectangleGeometry>(),
//                std::make_shared<TextureMaterial>(*depthTexture));
//        shadowDisplay->setPosition(glm::vec3(-1.0f, 3.0f, 0.0f));
//        m_scene->add(shadowDisplay);

        std::shared_ptr<Geometry> rectangle = std::make_shared<RectangleGeometry>(20.0f, 20.0f);
        auto floor = std::make_shared<Mesh>("floor", rectangle, shadowMaterial);
        floor->rotateX(-3.14 / 2, true);
        m_scene->add(floor);
    }

    void update() override {
        // view dynamic shadows -- need to increase shadow camera range
//        glm::vec3 target = glm::vec3(-2.0f, 0.0f, 2.0f * std::sin(m_deltaTimeSeconds));
//        auto direction = m_directionalLight->position() - target;
//        m_directionalLight->setDirection(glm::normalize(direction));
        // dirLight.lookAt(target);

        m_rig->update(m_input, m_deltaTimeSeconds);
        m_renderer->render(m_scene, m_camera);

        // render scene from shadow camera
        // auto shadowCam = m_renderer->shadowObject->camera;
        // m_renderer->render( m_scene, shadowCam );
    }

private:
    std::shared_ptr<Renderer> m_renderer{};
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<MovementRig> m_rig{};
    std::shared_ptr<DirectionalLight> m_directionalLight{};
};

int main() {
    Test_6_05().run(800, 600, "Shadows Example");
    return 0;
}
