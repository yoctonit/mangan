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

        geometry = std::make_shared<Rectangle>(4.0f, 4.0f);
        gridTex = std::make_shared<Texture>("images/grid.png");

        material = std::make_shared<Material>("shader/Test_5_3.vert", "shader/Test_5_3.frag");
        material->addUniform("texture", Mn::Shader::Uniform());
        material->addUniform("time", Mn::Shader::Uniform());
        material->locateUniforms();

        mesh = std::make_shared<Mesh>(geometry, material);
        scene.add(mesh);
    }

    void draw() {
        renderer->render(scene, camera);
    }

    void update(const Mn::Input& input, double delta_time) {
        static double time = 0.0;
        time += delta_time;
        material->uniforms["texture"].upload(gridTex->textureRef, 1);
        material->uniforms["time"].upload((float)time);
//        mesh->rotateY(0.0123f, true);
//        mesh->rotateX(0.0237f, true);
    }

    void cleanup() {}

private:
    std::shared_ptr<Renderer> renderer{};
    Scene scene{};
    Camera camera{};
    std::shared_ptr<Rectangle> geometry;
    std::shared_ptr<Texture> gridTex;
    std::shared_ptr<Material> material;
    std::shared_ptr<Mesh> mesh;

};

int main() {
    Mn::Window window(800, 800, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
