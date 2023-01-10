#include "Run.h"
#include "Shader.h"
#include "Input.h"
#include "Attribute.h"
//#include "geometry/Geometry.h"
//#include "geometry/Rectangle.h"
//#include "Rectangle.h"
#include "Material.h"
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
//#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>

class Scene3d {
public:
 Renderer renderer;
 Scene scene;
 Camera camera;
 Mesh mesh;

    Scene3d() = default;

    ~Scene3d() = default;

    void initialize(int, int) {
        renderer = new Renderer();
        scene = new Scene();
        camera = new Camera();
        camera.setPosition( new Vector(0,0,3) );
        Geometry geometry = new Rectangle();
        Material material = new SurfaceMaterial();
// to change value from default, for example:
// material.renderSettings.get("pointSize").data = 32;
        material.uniforms.get("useVertexColors").data = 1;
        mesh = new Mesh( geometry, material );
        scene.add( mesh );

    }

    void draw() const {
        renderer.render(scene, camera);
    }

    void update(const Mn::Input &input, double delta_time) {
                mesh.rotateY( 0.0123f, true );
        mesh.rotateX( 0.0237f, true );

    }

    void cleanup() {}
};

int main() {
    Mn::Window window(800, 800, "Scene3d");
    Scene3d scene;
    Mn::Run<Scene3d>(scene, window);
    return 0;
}
