#include "Run.h"
#include "Input.h"
#include "geometry/Axes.h"
#include "geometry/Box.h"
#include "geometry/MovementRig.h"
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
        renderer->setClearColor(glm::vec3 (.5f,.5f,.5f));
        camera = std::make_shared<Camera>();
        camera->setPosition(glm::vec3(-1.5f, -1.0f, 4.0f));
        camera->rotateZ(M_PI, true);

        rig = std::make_shared<MovementRig>();
        rig->attach( camera );
        rig->setPosition( glm::vec3(0.5f, 1.0f, 4.0f) );
        scene.add( rig );

        geometry = std::make_shared<Box>(1.0f, 2.0f, 1.0f);
        material = std::make_shared<SurfaceMaterial>();
        mesh = std::make_shared<Mesh>(geometry, material);
        scene.add(mesh);


//        std::shared_ptr<GridHelper> grid = std::make_shared<GridHelper>(10.0f,10, glm::vec3 (1.0f,1.0f,0.0f), glm::vec3 (1.0f,1.0f,1.0f), 2);
//        grid->rotateX(-M_PI/2.0f, true);
//        scene.add( grid );
        std::shared_ptr<AxesHelper> axes =std::make_shared<AxesHelper>(2.0f, 4);
        axes->translate(0.0f, 0.01f, 0.0f, true);
        scene.add( axes );
    }

    void draw() {
        renderer->render(scene, *camera);
    }

    void update(const Mn::Input &input, double delta_time) {
        rig->update(input, delta_time);
//        mesh->rotateY(0.0123f, true);
//        mesh->rotateX(0.0237f, true);
    }

    void cleanup() {}

private:
    std::shared_ptr<Renderer> renderer{};
    Scene scene{};
    std::shared_ptr<Camera> camera;
    std::shared_ptr<MovementRig> rig;
    std::shared_ptr<Box> geometry;
    std::shared_ptr<Material> material;
    std::shared_ptr<Mesh> mesh;

};

int main() {
    Mn::Window window(800, 800, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
