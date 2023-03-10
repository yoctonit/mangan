#include "Run.h"
#include "Input.h"
#include "dgf/geometry/Rectangle.h"
#include "dgf/material/SurfaceMaterial.h"
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
        camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
        geometry = std::make_shared<Rectangle>(2.0f, 4.0f);
        material = std::make_shared<SurfaceMaterial>();
        material->useVertexColors(true);
        // to change value from default, for example:
        // material.renderSettings.get("pointSize").data = 32;
        // material.uniforms["useVertexColors"]._data = true;
        mesh = std::make_shared<Mesh>(geometry, material);
        scene.add(mesh);
    }

    void draw() {
        renderer->render(scene, camera);
    }

    void update(const Mn::Input& input, double delta_time) {
        mesh->rotateY(0.0123f, true);
        mesh->rotateX(0.0237f, true);
    }

    void cleanup() {}

private:
    std::shared_ptr<Renderer> renderer{};
    Scene scene{};
    Camera camera{};
    std::shared_ptr<Rectangle> geometry;
    std::shared_ptr<Material> material;
    std::shared_ptr<Mesh> mesh;

};

int main() {
    Mn::Window window(800, 800, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
