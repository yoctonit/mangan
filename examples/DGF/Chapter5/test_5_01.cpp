#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "geometry/RectangleGeometry.h"
#include "material/TextureMaterial.h"


class Test_5_01 : public Base {
public:
    void initialize() override {
        Renderer::initialize();

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.0f, 0.0f, 2.0f));

        auto geometry = std::make_shared<RectangleGeometry>();
        Texture grid("images/grid.png");
        auto material = std::make_shared<TextureMaterial>(grid);

        m_mesh = std::make_shared<Mesh>("textured_rectangle", geometry, material);
        m_scene->add(m_mesh);
    }

    void update() override {
        // m_mesh->rotateY(0.01334, true);
        // m_mesh->rotateX(0.02345, true);
        Renderer::render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Mesh> m_mesh;
};

int main() {
    Test_5_01().run();
    return 0;
}
