#include "Run.h"
#include "Input.h"
#include "dgf/geometry/Rectangle.h"
#include "dgf/material/TextureMaterial.h"
#include "dgf/Texture.h"
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
        camera.setPosition(glm::vec3(0.0f, 0.0f, 1.5f));

        box = std::make_shared<Rectangle>(4.0f, 4.0f);
        boxMaterial = std::make_shared<TextureMaterial>("images/crate.png");
        meshBox = std::make_shared<Mesh>(box, boxMaterial);
        scene.add(meshBox);
        
        labelMaterial = std::make_shared<TextureMaterial>("images/grid.png");
        label = std::make_shared<Rectangle>(1.0f, 1.0f);
        meshLabel = std::make_shared<Mesh>(label, labelMaterial);
        scene.add(meshLabel);
    }

    void draw() {
        renderer->render(scene, camera);
    }

    void update(const Mn::Input& input, double delta_time) {
//        meshBox->rotateY(0.0123f, true);
//        meshBox->rotateX(0.0237f, true);
        if (input.is_pressed(Mn::key::up)) {
            glm::vec3 p = camera.getPosition();
            p.z -= 0.1f;
            camera.setPosition(p);
        }
        if (input.is_pressed(Mn::key::down)) {
            glm::vec3 p = camera.getPosition();
            p.z += 0.1f;
            camera.setPosition(p);
        }
        if (input.is_pressed(Mn::key::left)) {
            glm::vec3 p = camera.getPosition();
            p.x -= 0.1f;
            camera.setPosition(p);
        }
        if (input.is_pressed(Mn::key::right)) {
            glm::vec3 p = camera.getPosition();
            p.x += 0.1f;
            camera.setPosition(p);
        }
        meshLabel->lookAt(camera.getWorldPosition());
    }

    void cleanup() {}

private:
    std::shared_ptr<Renderer> renderer{};
    Scene scene{};
    Camera camera{};
    std::shared_ptr<Rectangle> box;
    std::shared_ptr<Rectangle> label;
    std::shared_ptr<Texture> labelTex;
    std::shared_ptr<Material> boxMaterial;
    std::shared_ptr<Material> labelMaterial;
    std::shared_ptr<Mesh> meshBox;
    std::shared_ptr<Mesh> meshLabel;
};

int main() {
    Mn::Window window(800, 800, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
