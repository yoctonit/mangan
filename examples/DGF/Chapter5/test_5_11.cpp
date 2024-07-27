#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/RenderTarget.h"
#include "core/Mesh.h"
#include "geometry/RectangleGeometry.h"
#include "geometry/BoxGeometry.h"
#include "geometry/SphereGeometry.h"
#include "material/TextureMaterial.h"
#include "material/SurfaceMaterial.h"
#include "extras/MovementRig.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/transform.hpp"


class Test_5_11 : public Base {
public:
    void initialize() override {
        m_renderer = std::make_shared<Renderer>();
        m_renderer->setDimensions(800, 600);

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPerspective(60.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
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

        // extra code
        std::shared_ptr<Geometry> sphereGeometry = std::make_shared<SphereGeometry>();
        Texture grid("images/grid.png");
        auto sphereMaterial = std::make_shared<TextureMaterial>(grid);
        m_sphere = std::make_shared<Mesh>("sphere", sphereGeometry, sphereMaterial);
        // sphere.setPosition( new Vector(-1.2, 1, 0) );
        m_sphere->applyMatrix(glm::translate(glm::vec3(-1.2f, 1.0f, 0.0f)), true);
        m_scene->add(m_sphere);

        std::shared_ptr<Geometry> boxGeometry = std::make_shared<BoxGeometry>(2.0f, 2.0f, 0.2f);
        auto boxMaterial = std::make_shared<SurfaceMaterial>();
        boxMaterial->uniforms()["baseColor"].data().m_dataVec3 = glm::vec3(0.2f, 0.2f, 0.2f);
        auto box = std::make_shared<Mesh>("box", boxGeometry, boxMaterial);
        // box.setPosition( new Vector(1.2, 1, 0) );
        box->applyMatrix(glm::translate(glm::vec3(1.2f, 1.0f, 0.0f)), true);
        m_scene->add(box);

        m_renderTarget = std::make_shared<RenderTarget>(512, 512);

        std::shared_ptr<Geometry> screenGeometry = std::make_shared<RectangleGeometry>(1.8f, 1.8f);
        auto screenMaterial = std::make_shared<TextureMaterial>(*m_renderTarget->texture);
        auto screen = std::make_shared<Mesh>("screen", screenGeometry, screenMaterial);
        // screen.setPosition( new Vector(1.2, 1, 0.11) );
        screen->applyMatrix(glm::translate(glm::vec3(1.2f, 1.0f, 0.11f)), true);
        m_scene->add(screen);

        m_skyCamera = std::make_shared<Camera>(); // aspectRatio=1 by default, as needed
        m_skyCamera->setPosition(glm::vec3(0.0f, 10.0f, 0.1f));
        // m_scene->add( m_skyCamera );
        // m_skyCamera->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f)); // not needed; camera by default looks at 0.0;
    }

    void update() override {
        m_rig->update(m_input, m_deltaTimeSeconds);
        m_sphere->rotateY(0.01337f, true);

        m_renderer->renderTarget = m_renderTarget;
        m_renderer->render(m_scene, m_skyCamera);
        m_renderer->renderTarget = nullptr;
        m_renderer->render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Renderer> m_renderer{};
    std::shared_ptr<RenderTarget> m_renderTarget{};
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Camera> m_skyCamera{};
    std::shared_ptr<MovementRig> m_rig;
    std::shared_ptr<Mesh> m_sphere;
};

int main() {
    Test_5_11().run(800, 600, "RenderTarget Example");
    return 0;
}
