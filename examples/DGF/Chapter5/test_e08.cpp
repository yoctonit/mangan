#include "Run.h"
#include "Input.h"
#include "dgf/geometry/Rectangle.h"
#include "dgf/material/SpriteMaterial.h"
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
        camera.rotateY(3.14f, true);

        geometry = std::make_shared<Rectangle>(1.0f, 1.0f);
        material = std::make_shared<SpriteMaterial>("images/rolling-ball.png");
        material->billboard(true);
        material->tileNumber(0);
        material->tileCount(glm::vec2(4.0f, 4.0f));
        mesh = std::make_shared<Mesh>(geometry, material);
        scene.add(mesh);
    }

    void draw() {
        renderer->render(scene, camera);
    }

    void update(const Mn::Input& input, double delta_time) {
        static double time = 0.0;
        const int tilesPerSecond = 8;
        time += delta_time;

        auto tileNumber = (float)std::floor(time * (double)tilesPerSecond);
        material->tileNumber(tileNumber);
//        Mn::Shader::UploadUniform(mesh->material->uniforms["tileNumber"], tileNumber);

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
    }

    void cleanup() {}

private:
    std::shared_ptr<Renderer> renderer{};
    Scene scene{};
    Camera camera{};
    std::shared_ptr<Rectangle> geometry;
    std::shared_ptr<SpriteMaterial> material;
    std::shared_ptr<Mesh> mesh;
};

int main() {
    Mn::Window window(800, 800, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
