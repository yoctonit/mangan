#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "geometry/SphereGeometry.h"
#include "material/Material.h"


class Test_4_05 : public Base {
public:
    void initialize() override {
        Renderer::initialize();

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.0f, 0.0f, 7.0f));

        std::shared_ptr<Geometry> geometry = std::make_shared<SphereGeometry>(3.0f, 128, 64);

        auto material = std::make_shared<Material>(
                "shader/Test_4_05.vert",
                "shader/Test_4_05.frag"
        );
        material->addUniform("time", 0.0f);

        m_mesh = std::make_shared<Mesh>("sphere", geometry, material);
        m_scene->add(m_mesh);

        m_time = 0.0f;
    }

    void update() override {
        m_time += 1.0f / 60.0f;
        m_mesh->material()->uniforms()["time"].data().m_dataFloat = m_time;
        Renderer::render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Mesh> m_mesh{};
    float m_time{};
};

int main() {
    Test_4_05().run();
    return 0;
}
