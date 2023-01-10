#include "Run.h"
#include "Input.h"
#include "Shader.h"
#include "Attribute.h"
#include "geometry/Geometry.h"
#include "geometry/Rectangle.h"
#include "material/Material.h"
#include "material/SurfaceMaterial.h"
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include <memory>
//#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>

class Scene3d {
public:
    Renderer renderer{};
    Scene scene{};
    Camera camera{};
    std::shared_ptr<Mesh> mesh;

    Scene3d() = default;

    ~Scene3d() = default;

    void initialize(int, int) {
//        camera.setPosition(new Vector(0, 0, 3));
        Rectangle geometry;
        SurfaceMaterial material;
//        Geometry geometry = new Rectangle();
//        Material material = new SurfaceMaterial();
        // to change value from default, for example:
        // material.renderSettings.get("pointSize").data = 32;
//        material.uniforms["useVertexColors"]._data = true;
        mesh = std::make_shared<Mesh>(geometry, material);
        scene.add(mesh);
    }

    void draw() const {
        renderer.render(scene, camera);
    }

    void update(const Mn::Input &input, double delta_time) {
        mesh->rotateY(0.0123f, true);
        mesh->rotateX(0.0237f, true);
    }

    void cleanup() {}
};

int main() {
    Mn::Window window(800, 800, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
