#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "geometry/RectangleGeometry.h"
#include "material/TextureMaterial.h"


class Test_5_05 : public Base {
public:
    void initialize() override {
        Renderer::initialize();

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.0f, 0.0f, 1.5f));

        std::shared_ptr<Geometry> geometry = std::make_shared<RectangleGeometry>();

        Texture gridTexture("images/grid.png");
        Texture noiseTexture("images/noise.png");

        auto distortMaterial = std::make_shared<Material>("shader/Test_5_03.vert", "shader/Test_5_05.frag");
        distortMaterial->addUniform("image", gridTexture.textureRef(), 1);
        distortMaterial->addUniform("noise", noiseTexture.textureRef(), 2);
        distortMaterial->addUniform("time", 0.0f);

        m_mesh = std::make_shared<Mesh>("object", geometry, distortMaterial);
        m_scene->add(m_mesh);
    }

    void update() override {
        m_mesh->material()->uniforms()["time"].data().m_dataFloat = (float) m_timeSeconds;
        Renderer::render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Mesh> m_mesh{};
};

int main() {
    Test_5_05().run();
    return 0;
}
