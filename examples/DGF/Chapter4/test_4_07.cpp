#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "geometry/CylindricalGeometry.h"
#include "extras/AxesHelper.h"
#include "extras/GridHelper.h"
#include "extras/MovementRig.h"
#include "material/SurfaceMaterial.h"


class Test_4_06 : public Base {
public:
    void initialize() override {
        Renderer::initialize();

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.5f, 1.0f, 4.0f));

        auto grid = std::make_shared<GridHelper>(
                10.0f, 10.0f,
                glm::vec3(1.0f, 1.0f, 0.0f),
                glm::vec3(1.0f, 1.0f, 1.0f),
                2.0f);
        grid->rotateX(-M_PI / 2.0f, true);
        m_scene->add(grid);

        auto axes = std::make_shared<AxesHelper>(2.0f, 8.0f);
        axes->translate(0.0f, 0.01, 0.0f, true);
        m_scene->add(axes);

        m_rig = std::make_shared<MovementRig>();
        m_rig->attach(m_camera);
        // m_rig->setPosition(glm::vec3(0.5f, 1.0f, 4.0f));
        m_scene->add(m_rig);

        std::shared_ptr<CylindricalGeometry> geometry = std::make_shared<CylindricalGeometry>(
                1.0f, 1.0f, 1.0f,
                32, 4, false, true
        );
        std::shared_ptr<Material> material = std::make_shared<SurfaceMaterial>();
        material->uniforms()["useVertexColors"].data().m_dataBool = true;
        // material->renderSettings().set(RenderSettings::Type::DoubleSide, true);

        auto mesh = std::make_shared<Mesh>("object", geometry, material);
        m_scene->add(mesh);
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
    Test_4_06().run();
    return 0;
}
