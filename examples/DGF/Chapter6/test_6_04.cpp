#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/RenderTarget.h"
#include "core/Mesh.h"
#include "geometry/RectangleGeometry.h"
#include "geometry/SphereGeometry.h"
#include "material/SurfaceMaterial.h"
#include "material/TextureMaterial.h"
#include "extras/MovementRig.h"
#include "extras/Postprocessor.h"
#include "effects/AdditiveBlendEffect.h"
#include "effects/BrightFilterEffect.h"
#include "effects/HorizontalBlurEffect.h"
#include "effects/VerticalBlurEffect.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/transform.hpp"


class Test_6_04 : public Base {
public:
    void initialize() override {
        m_renderer = std::make_shared<Renderer>();
        m_renderer->setDimensions(800, 600);

        m_scene = std::make_shared<Scene>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPerspective(60.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
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
        // glow scene
        auto glowScene = std::make_shared<Scene>("glow-scene");
        auto redMaterial = std::make_shared<SurfaceMaterial>();
        redMaterial->uniforms()["baseColor"].data().m_dataVec3 = glm::vec3(1.0f, 0.0f, 0.0f);
        auto glowSphere = std::make_shared<Mesh>("glow-sphere", sphereGeometry, redMaterial);
        glowSphere->setTransform(m_sphere->transform());
        glowScene->add(glowSphere);

        // glow postprocessing
        glm::vec2 size(800, 600);
        auto glowTarget = std::make_shared<RenderTarget>(800, 600);
        m_glowPass = std::make_shared<Postprocessor>(m_renderer, glowScene, m_camera, glowTarget);

        // empty spots have no initialized values, causing no glow blur...
        m_glowPass->addEffect(std::make_shared<HorizontalBlurEffect>(size, 50));
        m_glowPass->addEffect(std::make_shared<VerticalBlurEffect>(size, 50));

        // combining results of glow effect with main scene
        m_comboPass = std::make_shared<Postprocessor>(m_renderer, m_scene, m_camera, nullptr);
        m_comboPass->addEffect(std::make_shared<AdditiveBlendEffect>(*glowTarget->texture, 1, 3));
    }

    void update() override {
        m_rig->update(m_input, m_deltaTimeSeconds);

        m_sphere->rotateY(0.01337f, true);

        m_glowPass->render();
        m_comboPass->render();
    }

private:
    std::shared_ptr<Renderer> m_renderer{};
    std::shared_ptr<Postprocessor> m_glowPass{};
    std::shared_ptr<Postprocessor> m_comboPass{};
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<MovementRig> m_rig;
    std::shared_ptr<Mesh> m_sphere;
};

int main() {
    Test_6_04().run(800, 600, "Glow Effect Example");
    return 0;
}
