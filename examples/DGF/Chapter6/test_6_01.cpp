#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/RenderTarget.h"
#include "core/Mesh.h"
#include "geometry/SphereGeometry.h"
#include "extras/DirectionalLightHelper.h"
#include "extras/PointLightHelper.h"
#include "material/FlatMaterial.h"
#include "material/LambertMaterial.h"
#include "material/PhongMaterial.h"
#include "light/AmbientLight.h"
#include "light/DirectionalLight.h"
#include "light/PointLight.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/transform.hpp"


class Test_6_01 : public Base {
public:
    void initialize() override {
        m_renderer = std::make_shared<Renderer>();
        m_renderer->setDimensions(1600, 1200);
        m_renderer->setClearColor(glm::vec3(0.4f, 0.4f, 0.4f));

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPerspective(60.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
        m_camera->setPosition(glm::vec3(0.0f, 0.0f, 6.0f));

        m_renderer->light0 = std::make_shared<AmbientLight>(glm::vec3(0.1f, 0.1f, 0.1f));

        m_directionalLight = std::make_shared<DirectionalLight>(
                glm::vec3(0.8f, 0.8f, 0.8f),
                glm::vec3(-1.0f, -1.0f, -2.0f)
        );
        m_renderer->light1 = m_directionalLight;

        m_pointLight = std::make_shared<PointLight>(
                glm::vec3(0.9f, 0.0f, 0.0f),
                glm::vec3(1.0f, 1.0f, 0.8f)
        );
        m_renderer->light2 = m_pointLight;

        m_directionalLightHelper = std::make_shared<DirectionalLightHelper>(m_directionalLight);
        m_directionalLightHelper->setTransform(glm::translate(glm::vec3(3.0f, 2.0f, 0.0f)));
        // m_directionalLightHelper->setDirection(); not implemented
        m_scene->add(m_directionalLightHelper);

        m_pointLightHelper = std::make_shared<PointLightHelper>(m_pointLight);
        m_pointLightHelper->setTransform(glm::translate(m_pointLight->position()));
        m_scene->add(m_pointLightHelper);

        std::shared_ptr<Geometry> sphereGeometry = std::make_shared<SphereGeometry>();

        auto flatMaterial = std::make_shared<FlatMaterial>(nullptr);
        flatMaterial->uniforms()["baseColor"].data().m_dataVec3 = glm::vec3(0.6f, 0.2f, 0.2f);
        auto sphere1 = std::make_shared<Mesh>("sphere1", sphereGeometry, flatMaterial);
        sphere1->applyMatrix(glm::translate(glm::vec3(-2.2f, 0.0f, 0.0f)), true);
        m_scene->add(sphere1);

        auto grid = std::make_shared<Texture>("images/grid.png");
        auto lambertMaterial = std::make_shared<LambertMaterial>(grid);
        auto sphere2 = std::make_shared<Mesh>("sphere2", sphereGeometry, lambertMaterial);
        sphere2->applyMatrix(glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)), true);
        m_scene->add(sphere2);

        auto phongMaterial = std::make_shared<PhongMaterial>(nullptr);
        phongMaterial->uniforms()["baseColor"].data().m_dataVec3 = glm::vec3(0.5f, 0.5f, 1.0f);
        auto sphere3 = std::make_shared<Mesh>("sphere3", sphereGeometry, phongMaterial);
        sphere3->applyMatrix(glm::translate(glm::vec3(2.2f, 0.0f, 0.0f)), true);
        m_scene->add(sphere3);
    }

    void update() override {
        m_directionalLight->setDirection(glm::vec3(-1.0f, std::sin(0.7f * m_timeSeconds), -2.0f));
        m_pointLight->setPosition(glm::vec3(1.0f, std::sin(m_timeSeconds), 0.8f));
        m_pointLightHelper->setTransform(glm::translate(m_pointLight->position()));
        m_renderer->render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Renderer> m_renderer{};
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<DirectionalLight> m_directionalLight;
    std::shared_ptr<DirectionalLightHelper> m_directionalLightHelper;
    std::shared_ptr<PointLight> m_pointLight;
    std::shared_ptr<PointLightHelper> m_pointLightHelper;
};

int main() {
    Test_6_01().run(1600, 1200, "Light Example");
    return 0;
}
