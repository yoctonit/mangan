#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/RenderTarget.h"
#include "core/Mesh.h"
#include "geometry/RectangleGeometry.h"
#include "geometry/SphereGeometry.h"
#include "material/TextureMaterial.h"
#include "extras/MovementRig.h"
#include "extras/Postprocessor.h"
#include "effects/ColorReduceEffect.h"
#include "effects/InvertEffect.h"
#include "effects/PixelateEffect.h"
#include "effects/TintEffect.h"
#include "effects/VignetteEffect.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/transform.hpp"


class Test_6_03 : public Base {
public:
    void initialize() override {
        m_renderer = std::make_shared<Renderer>();
        m_renderer->setDimensions(1024, 1024);

        m_scene = std::make_shared<Scene>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.0f, 1.0f, 4.0f));

        m_rig = std::make_shared<MovementRig>();
        m_rig->attach(m_camera);
        m_scene->add(m_rig);

        std::shared_ptr<Geometry> skyGeometry = std::make_shared<SphereGeometry>(50.0f);
        Texture skyTexture("images/sky-earth.jpg");
        auto skyMaterial = std::make_shared<TextureMaterial>(skyTexture);
        auto sky = std::make_shared<Mesh>("sky", skyGeometry, skyMaterial);
        m_scene->add(sky);

        std::shared_ptr<Geometry> grassGeometry = std::make_shared<RectangleGeometry>(100.0f, 100.0f);
        Texture grassTexture("images/grass.jpg");
        auto grassMaterial = std::make_shared<TextureMaterial>(grassTexture);
        grassMaterial->uniforms()["repeatUV"].data().m_dataVec2 = glm::vec2(50.0f, 50.0f);
        auto grass = std::make_shared<Mesh>("grass", grassGeometry, grassMaterial);
        grass->rotateX(-3.14f / 2.0f, true);
        m_scene->add(grass);

        std::shared_ptr<Geometry> sphereGeometry = std::make_shared<SphereGeometry>();
        Texture grid("images/grid.png");
        auto sphereMaterial = std::make_shared<TextureMaterial>(grid);
        m_sphere = std::make_shared<Mesh>("sphere", sphereGeometry, sphereMaterial);
        m_sphere->applyMatrix(glm::translate(glm::vec3(0.0f, 1.0f, 0.0f)), true);
        m_scene->add(m_sphere);

        // set up postprocessing
        m_postprocessor = std::make_shared<Postprocessor>(m_renderer, m_scene, m_camera, nullptr);
        // m_postprocessor->addEffect(std::make_shared<TintEffect>(glm::vec3(1.0f, 0.0f, 0.0f)));
        // m_postprocessor->addEffect(std::make_shared<InvertEffect>() );
        // m_postprocessor->addEffect(std::make_shared<PixelateEffect>(8.0f, glm::vec2(800.0f, 600.0f)));
        // m_postprocessor->addEffect(std::make_shared<VignetteEffect>(0.4f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
        // m_postprocessor->addEffect(std::make_shared<ColorReduceEffect>(3));

        // retro handheld video game system effect
        m_postprocessor->addEffect(std::make_shared<TintEffect>(glm::vec3(0.0f, 1.0f, 0.0f)));
        m_postprocessor->addEffect(std::make_shared<ColorReduceEffect>(5));
        m_postprocessor->addEffect(std::make_shared<PixelateEffect>(8.0f, glm::vec2(800.0f, 600.0f)));
    }

    void update() override {
        m_rig->update(m_input, m_deltaTimeSeconds);

        m_sphere->rotateY(0.01337f, true);

        // m_renderer->render(m_scene, m_camera);
        m_postprocessor->render();
    }

private:
    std::shared_ptr<Renderer> m_renderer{};
    // std::shared_ptr<RenderTarget> m_renderTarget{};
    std::shared_ptr<Postprocessor> m_postprocessor{};
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<MovementRig> m_rig;
    std::shared_ptr<Mesh> m_sphere;
};

int main() {
    Test_6_03().run();
    return 0;
}
