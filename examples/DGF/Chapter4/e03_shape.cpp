#include "Run.h"
#include "Input.h"
#include "geometry/Geometry.h"
#include "material/LineMaterial.h"
#include "material/PointMaterial.h"
#include "dgf/Mesh.h"
#include "dgf/Scene.h"
#include "dgf/Camera.h"
#include "dgf/Renderer.h"
#include <memory>

class Scene3d {
public:
    void initialize(int, int) {
        renderer = std::make_shared<Renderer>();
        renderer->setClearColor(glm::vec3(0.5f, 0.5f, 0.5f));
        camera.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

        geometry = std::make_shared<Geometry>();
        std::vector<glm::vec3> positionList;
        for (float x=-3.2f; x <= 3.2f; x += 0.3f)
            positionList.emplace_back( x, std::sin(x), 0.0f );

        glm::vec3 R(1, 0, 0);
        glm::vec3 Y(1, 1, 0);
        glm::vec3 G(0, 0.25, 0);
        std::vector<glm::vec3> colorList{R,G,Y, Y,G,G, Y,G,R};

        geometry->addAttribute("vertexPosition", std::make_shared<Mn::Shader::AttributeVector3>(Geometry::toVector(positionList)));
//        geometry->addAttribute("vertexColor", std::make_shared<Mn::Shader::AttributeVector3>(Geometry::toVector(colorList)));
        geometry->vertexCount = positionList.size();

        lineMaterial = std::make_shared<LineMaterial>("connected");
        lineMaterial->baseColor(glm::vec3(1.0f,0.0f,1.0f));
        lineMaterial->useVertexColors(false);
        lineMaterial->addRenderSetting("lineWidth", 4.0f, true);
        auto lineMesh = std::make_shared<Mesh>(geometry, lineMaterial);
        scene.add( lineMesh );

        pointMaterial = std::make_shared<PointMaterial>();
        pointMaterial->baseColor(glm::vec3(1.0f,1.0f,0.0f));
        pointMaterial->useVertexColors(false);
        pointMaterial->addRenderSetting("pointSize", 8.0f, true);
        auto pointMesh = std::make_shared<Mesh>(geometry, pointMaterial);
        scene.add( pointMesh );
    }

    void draw() {
        renderer->render(scene, camera);
    }

    void update(const Mn::Input &input, double delta_time) {
//        mesh->rotateY(0.0123f, true);
//        mesh->rotateX(0.0237f, true);
        if (input.is_clicked(Mn::key::up)) {
            glm::vec3 p = camera.getPosition();
            p.z -= 0.1f;
            camera.setPosition(p);
        }
        if (input.is_clicked(Mn::key::down)) {
            glm::vec3 p = camera.getPosition();
            p.z += 0.1f;
            camera.setPosition(p);
        }
    }

    void cleanup() {}

private:
    std::shared_ptr<Renderer> renderer{};
    Scene scene{};
    Camera camera{};
    std::shared_ptr<Geometry> geometry;
    std::shared_ptr<Material> lineMaterial;
    std::shared_ptr<Material> pointMaterial;
    std::shared_ptr<Mesh> mesh;
};

int main() {
    Mn::Window window(800, 800, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
