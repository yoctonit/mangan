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
        camera = std::make_shared<Camera>(60.0, 800.0f / 600.0f, 0.1f, 1000.0f);
        renderer = std::make_shared<Renderer>();
        renderer->setClearColor(glm::vec3(0.5f, 0.5f, 0.5f));
        camera->setPosition(glm::vec3(0.0f, 1.5f, 5.0f));
        camera->rotateY(3.14f, true);

        geometry = std::make_shared<Rectangle>(1.0f, 1.0f);
        material = std::make_shared<TextureMaterial>("images/crate.png");
        mesh = std::make_shared<Mesh>(geometry, material);
        scene.add(mesh);

        hudCamera = std::make_shared<Camera>();
        hudCamera->setOrthographic(0.0f, 800.0f, 0.0f, 600.0f, 1.0f, -1.0f);

        labelGeo1 = std::make_shared<Rectangle>(600.0f, 80.0);
        labelGeo1->position(glm::vec2(0.0f, 600.0f));
        labelGeo1->alignment(glm::vec2(0.0f, 1.0f));
        labelMat1 = std::make_shared<TextureMaterial>("images/crate-sim.png");
        label1 = std::make_shared<Mesh>(labelGeo1, labelMat1);
        hudScene.add(label1);

        labelGeo2 = std::make_shared<Rectangle>(400.0f, 80.0);
        labelGeo2->position(glm::vec2(500.0f, 0.0f));
        labelGeo2->alignment(glm::vec2(0.5f, 0.5f));
        labelMat2 = std::make_shared<TextureMaterial>("images/version-1.png");
        label2 = std::make_shared<Mesh>(labelGeo2, labelMat2);
        hudScene.add(label2);
    }

    void draw() {
        renderer->clearColorBuffer = true;
        renderer->render(scene, *camera);
        renderer->clearColorBuffer = false;
        renderer->render(hudScene, *hudCamera);
    }

    void update(const Mn::Input &input, double delta_time) {
//        static double time = 0.0;
//        time += delta_time;
        if (input.is_pressed(Mn::key::up)) {
            glm::vec3 p = camera->getPosition();
            p.z -= 0.1f;
            camera->setPosition(p);
        }
        if (input.is_pressed(Mn::key::down)) {
            glm::vec3 p = camera->getPosition();
            p.z += 0.1f;
            camera->setPosition(p);
        }
        if (input.is_pressed(Mn::key::left)) {
            glm::vec3 p = camera->getPosition();
            p.y -= 0.1f;
            camera->setPosition(p);
        }
        if (input.is_pressed(Mn::key::right)) {
            glm::vec3 p = camera->getPosition();
            p.y += 0.1f;
            camera->setPosition(p);
        }
    }

    void cleanup() {}

private:
    std::shared_ptr<Renderer> renderer{};
    Scene scene{};
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Rectangle> geometry;
    std::shared_ptr<TextureMaterial> material;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Mesh> label1;
    std::shared_ptr<Mesh> label2;
    Scene hudScene;
    std::shared_ptr<Camera> hudCamera;
    std::shared_ptr<Rectangle> labelGeo1;
    std::shared_ptr<TextureMaterial> labelMat1;
    std::shared_ptr<Rectangle> labelGeo2;
    std::shared_ptr<TextureMaterial> labelMat2;
};

int main() {
    Mn::Window window(800, 600, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
