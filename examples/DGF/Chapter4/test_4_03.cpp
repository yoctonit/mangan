#include <cmath>
#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "material/LineMaterial.h"
#include "material/PointMaterial.h"


class Test_4_03 : public Base {
public:
    void initialize() override {
        Renderer::initialize();

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.0f, 0.0f, 7.0f));

        std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>();

        std::vector<glm::vec3> positionList;
        float x = -3.2f;
        while (x <= 3.2f) {
            positionList.emplace_back(x, std::sin(x), 0.0f);
            x += 0.3f;
        }
        std::vector<float> positionData = Geometry::flatten(positionList);
        geometry->addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
        geometry->vertexCount(static_cast<int>(positionList.size()));

        auto lineMaterial = std::make_shared<LineMaterial>(LineMaterial::LineStyle::Connected);
        lineMaterial->uniforms()["baseColor"].data().m_dataVec3 = glm::vec3(1.0f, 0.0f, 1.0f);
        lineMaterial->renderSettings().set(RenderSettings::Type::LineWidth, 4.0f);
        auto lineMesh = std::make_shared<Mesh>("line", geometry, lineMaterial);
        m_scene->add(lineMesh);

        auto pointMaterial = std::make_shared<PointMaterial>();
        pointMaterial->uniforms()["baseColor"].data().m_dataVec3 = glm::vec3(1.0f, 1.0f, 0.0f);
        lineMaterial->renderSettings().set(RenderSettings::Type::PointSize, 8.0f);
        auto pointMesh = std::make_shared<Mesh>("points", geometry, pointMaterial);
        m_scene->add(pointMesh);
    }

    void update() override {
        Renderer::render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
};

int main() {
    Test_4_03().run();
    return 0;
}
