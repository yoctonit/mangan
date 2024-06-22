#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "geometry/BoxGeometry.h"
#include "material/SurfaceMaterial.h"


class Test_4_01 : public Base {
public:
    void initialize() override {
        Renderer::initialize();
        Renderer::setClearColor(glm::vec3(0.5f, 0.5f, 0.5f));

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.5f, 0.5f, 1.5f));

        std::shared_ptr<BoxGeometry> geometry = std::make_shared<BoxGeometry>();
        std::shared_ptr<Material> material = std::make_shared<SurfaceMaterial>();

        material->renderSettings().set(RenderSettings::Type::Wireframe, true);
        material->renderSettings().set(RenderSettings::Type::LineWidth, 4.0f);

        material->uniforms()["useVertexColors"].data().m_dataBool = true;

        m_mesh = std::make_shared<Mesh>("box", geometry, material);
        m_scene->add(m_mesh);
    }

    void update() override {
        m_mesh->rotateY(0.0123f, true);
        m_mesh->rotateX(0.0237f, true);
        Renderer::render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Mesh> m_mesh;
};

int main() {
    Test_4_01().run();
    return 0;
}
