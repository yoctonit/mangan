#include "Run.h"
#include "Input.h"
#include "geometry/Geometry.h"
#include "material/SurfaceMaterial.h"
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
        glm::vec3 P0(-0.1, 0.1, 0.0);
        glm::vec3 P1( 0.0, 0.0, 0.0);
        glm::vec3 P2( 0.1, 0.1, 0.0);
        glm::vec3 P3(-0.2, -0.2, 0.0);
        glm::vec3 P4( 0.2, -0.2, 0.0);
        std::vector<glm::vec3> positionList{P0,P3,P1, P1,P3,P4, P1,P4,P2};

        glm::vec3 R(1, 0, 0);
        glm::vec3 Y(1, 1, 0);
        glm::vec3 G(0, 0.25, 0);
        std::vector<glm::vec3> colorList{R,G,Y, Y,G,G, Y,G,R};

        geometry->addAttribute("vertexPosition", std::make_shared<Mn::Shader::AttributeVector3>(Geometry::toVector(positionList)));
        geometry->addAttribute("vertexColor", std::make_shared<Mn::Shader::AttributeVector3>(Geometry::toVector(colorList)));
        geometry->vertexCount = 9;

        material = std::make_shared<SurfaceMaterial>();

        mesh = std::make_shared<Mesh>(geometry, material);
        scene.add(mesh);
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
    std::shared_ptr<Material> material;
    std::shared_ptr<Mesh> mesh;
};

int main() {
    Mn::Window window(800, 800, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
