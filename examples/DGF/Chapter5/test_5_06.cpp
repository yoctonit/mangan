#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "geometry/RectangleGeometry.h"
#include "material/TextureMaterial.h"


class Test_5_06 : public Base {
public:
    void initialize() override {
        Renderer::initialize();

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.0f, 0.0f, 1.5f));

        std::shared_ptr<Geometry> geometry = std::make_shared<RectangleGeometry>();

        auto material = std::make_shared<Material>("shader/Test_5_06.vert", "shader/Test_5_06.frag");

        auto mesh = std::make_shared<Mesh>("object", geometry, material);
        m_scene->add(mesh);
    }

    void update() override {
        Renderer::render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
};

int main() {
    Test_5_06().run();
    return 0;
}
