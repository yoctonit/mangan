#include "Run.h"
#include "Input.h"
#include "geometry/Surface.h"
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
        camera.setPosition(glm::vec3(0.0f, 0.0f, 1.1f));
        geometry = std::make_shared<Sphere>(1.0f, 16.0f, 16.0f);
        material = std::make_shared<Material>("shader/BasicMaterial1.vert", "shader/BasicMaterial1.frag");
        material->locateUniforms();
        mesh = std::make_shared<Mesh>(geometry, material);
        scene.add(mesh);
    }

    void draw() {
        renderer->render(scene, camera);
    }

    void update(const Mn::Input &input, double delta_time) {
        mesh->rotateY(0.0123f, true);
        mesh->rotateX(0.0237f, true);
    }

    void cleanup() {}

private:
    std::shared_ptr<Renderer> renderer{};
    Scene scene{};
    Camera camera{};
    std::shared_ptr<Sphere> geometry;
    std::shared_ptr<Material> material;
    std::shared_ptr<Mesh> mesh;

};

int main() {
    Mn::Window window(800, 800, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
