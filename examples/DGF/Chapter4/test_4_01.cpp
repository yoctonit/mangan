#include "core/Base.h"
#include "core/Shader.h"
#include "core/Attribute.h"
#include "core/Uniform.h"
#include "core/Scene.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "geometry/BoxGeometry.h"
#include "material/SurfaceMaterial.h"


class Test_4_01 : public Base {
public:
    void initialize() override {
        m_renderer = std::make_shared<Renderer>();
        m_renderer->setClearColor(glm::vec3(0.5f, 0.5f, 0.5f));

        m_scene = std::make_shared<Scene>();

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.5f, 0.5f, 1.5f));

        std::shared_ptr<BoxGeometry> geometry = std::make_shared<BoxGeometry>();
        std::shared_ptr<Material> material = std::make_shared<SurfaceMaterial>();

        // to change value from default, for example:
        // material.renderSettings.get("pointSize").data = 32; // this doesn't work yet
        material->addRenderSetting(std::make_shared<RenderSettingWireframe>(true));
        material->addRenderSetting(std::make_shared<RenderSettingLineWidth>(8));

        material->uniforms()["useVertexColors"].data().m_dataBool = true;
//         material->useVertexColors(true);

        m_mesh = std::make_shared<Mesh>("box", geometry, material);
        m_scene->add(m_mesh);
    }

    void update() override {
        m_mesh->rotateY(0.0123f, true);
        m_mesh->rotateX(0.0237f, true);
        m_renderer->render(m_scene, m_camera);
//        Renderer::render1(m_mesh, m_camera);
    }

private:
    std::shared_ptr<Renderer> m_renderer{};
    std::shared_ptr<Scene> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Mesh> m_mesh;
};

int main() {
    Test_4_01().run();
    return 0;
}
