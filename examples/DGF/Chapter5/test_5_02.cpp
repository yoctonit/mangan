#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "geometry/RectangleGeometry.h"
#include "geometry/SphereGeometry.h"
#include "material/TextureMaterial.h"
#include "extras/MovementRig.h"


class Test_5_02 : public Base {
public:
    void initialize() override {
        Renderer::initialize();

        m_scene = std::make_shared<Object3D>("scene");

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
    }

    void update() override {
        m_rig->update(m_input, m_deltaTimeSeconds);
        Renderer::render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<MovementRig> m_rig;
};

int main() {
    Test_5_02().run();
    return 0;
}
