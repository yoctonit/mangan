#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "geometry/BoxGeometry.h"
#include "material/SurfaceMaterial.h"


class Test_4_02 : public Base {
public:
    void initialize() override {
        Renderer::initialize();
        // Renderer::setClearColor(glm::vec3(0.5f, 0.5f, 0.5f));

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

        std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>();

        glm::vec3 P0(-0.1f, 0.1f, 0.0f);
        glm::vec3 P1(0.0f, 0.0f, 0.0f);
        glm::vec3 P2(0.1f, 0.1f, 0.0f);
        glm::vec3 P3(-0.2f, -0.2f, 0.0f);
        glm::vec3 P4(0.2f, -0.2f, 0.0f);

        std::vector<glm::vec3> positionList{P0, P3, P1, P1, P3, P4, P1, P4, P2};
        std::vector<float> positionData;
        for (auto &p: positionList) {
            positionData.push_back(p.x);
            positionData.push_back(p.y);
            positionData.push_back(p.z);
        }

        glm::vec3 R(1.0f, 0.0f, 0.0f);
        glm::vec3 Y(1.0f, 1.0f, 0.0f);
        glm::vec3 G(0.0f, 0.25f, 0.0f);

        std::vector<glm::vec3> colorList{R, G, Y, Y, G, G, Y, G, R};
        std::vector<float> colorData;
        for (auto &c: colorList) {
            colorData.push_back(c.r);
            colorData.push_back(c.g);
            colorData.push_back(c.b);
        }

        geometry->addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
        geometry->addAttribute("vertexColor", Attribute::Type::Vec3, colorData);
        geometry->vertexCount(9);

        std::shared_ptr<Material> material = std::make_shared<SurfaceMaterial>();
        material->uniforms()["useVertexColors"].data().m_dataBool = true;

        m_mesh = std::make_shared<Mesh>("custom", geometry, material);
        m_scene->add(m_mesh);
    }

    void update() override {
        Renderer::render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Mesh> m_mesh;
};

int main() {
    Test_4_02().run();
    return 0;
}
